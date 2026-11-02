#include "gui/models/ScanController.hpp"

#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "domain/repositories/ITransactionManager.hpp"
#include "services/LibraryService.hpp"
#include "services/ScanProgress.hpp"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>
#include <QUrl>

#include <filesystem>
#include <memory>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace {

QString scanConnectionName() {
    return QStringLiteral("eight_track_scan");
}

/**
 * @brief Implementación de `ITransactionManager` para la conexión del hilo de
 * escaneo.
 */
class ScanTransactionManager : public ITransactionManager {
public:
    explicit ScanTransactionManager(const QSqlDatabase& database)
        : m_database(database) {}

    bool transaction() override { return m_database.transaction(); }
    bool commit() override { return m_database.commit(); }
    bool rollback() override { return m_database.rollback(); }

private:
    QSqlDatabase m_database;
};

/**
 * @brief Abre y cierra una conexión SQLite en el hilo de escaneo.
 */
class ScanDatabase {
public:
    explicit ScanDatabase(const std::filesystem::path& path) {
        const QString connection = scanConnectionName();
        m_database =
            QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), connection);
        m_database.setDatabaseName(QString::fromStdString(path.string()));

        if (!m_database.open()) {
            const QString error = m_database.lastError().text();
            m_database = QSqlDatabase();
            QSqlDatabase::removeDatabase(connection);
            throw std::runtime_error(error.toStdString());
        }

        QSqlQuery query(m_database);
        query.exec(QStringLiteral("PRAGMA foreign_keys = ON"));
        query.exec(QStringLiteral(
            "PRAGMA busy_timeout = 5000")); // Tiempo de espera por si acaso
    }

    ~ScanDatabase() {
        if (m_database.isOpen())
            m_database.close();

        m_database = QSqlDatabase();
        QSqlDatabase::removeDatabase(scanConnectionName());
    }

    ScanDatabase(const ScanDatabase&) = delete;
    ScanDatabase& operator=(const ScanDatabase&) = delete;

    [[nodiscard]] QSqlDatabase database() const { return m_database; }

private:
    QSqlDatabase m_database;
};

} // namespace

namespace Track8::Gui {

/**
 * @class ScanWorker
 * @brief Ejecuta el escaneo y la importación dentro de un `QThread`.
 */
class ScanWorker : public QObject {
    Q_OBJECT

public:
    ScanWorker(std::filesystem::path dbPath, std::filesystem::path coversDir,
               std::filesystem::path directory, QObject* parent = nullptr)
        : QObject(parent),
          m_dbPath(std::move(dbPath)),
          m_coversDir(std::move(coversDir)),
          m_directory(std::move(directory)) {}

public slots:
    void run();

signals:
    void progress(int current, int total, const QString& file);
    void finished(bool success, const QString& error);

private:
    std::filesystem::path m_dbPath;
    std::filesystem::path m_coversDir;
    std::filesystem::path m_directory;
};

void ScanWorker::run() {
    try {
        const ScanDatabase database(m_dbPath);

        const auto transactions =
            std::make_shared<ScanTransactionManager>(database.database());
        const auto albums = std::make_shared<Database::SQLiteAlbumRepository>(
            database.database());
        auto performers = std::make_shared<Database::SQLitePerformerRepository>(
            database.database());
        const auto songs = std::make_shared<Database::SQLiteSongRepository>(
            database.database(), performers, albums);

        const Services::LibraryService library(albums, performers, songs,
                                               m_coversDir, transactions);

        library.scan(m_directory, [this](const ScanProgress& progress) {
            emit this->progress(static_cast<int>(progress.current),
                                static_cast<int>(progress.total),
                                QString::fromStdString(progress.currentFile));
        });

        emit finished(true, {});
    } catch (const std::exception& exception) {
        emit finished(false, QString::fromUtf8(exception.what()));
    }
}

ScanController::ScanController(std::filesystem::path dbPath,
                               std::filesystem::path coversDir, QObject* parent)
    : QObject(parent),
      m_dbPath(std::move(dbPath)),
      m_coversDir(std::move(coversDir)) {}

ScanController::~ScanController() {
    if (m_thread) {
        m_thread->quit();
        m_thread->wait();
    }
}

void ScanController::start(const QUrl& directory) {
    if (m_running || m_thread)
        return;

    resetState();

    if (!directory.isLocalFile()) {
        setError(tr("The selected path is not a local directory."));
        emit finished(false);
        return;
    }

    const std::filesystem::path path(directory.toLocalFile().toStdString());
    if (std::error_code errorCode;
        !std::filesystem::is_directory(path, errorCode)) {
        setError(tr("The selected path is not a valid directory."));
        emit finished(false);
        return;
    }

    m_running = true;
    emit runningChanged();

    m_thread = new QThread(this);
    m_worker = new ScanWorker(m_dbPath, m_coversDir, path);
    m_worker->moveToThread(m_thread);

    connect(m_thread, &QThread::started, m_worker, &ScanWorker::run);
    connect(m_worker, &ScanWorker::progress, this, &ScanController::onProgress);
    connect(m_worker, &ScanWorker::finished, this, &ScanController::onFinished);
    connect(m_worker, &ScanWorker::finished, m_thread, &QThread::quit);
    connect(m_thread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(m_thread, &QThread::finished, m_thread, &QObject::deleteLater);
    connect(m_thread, &QThread::finished, this,
            &ScanController::onThreadFinished);

    m_thread->start();
}

void ScanController::onProgress(const int current, const int total,
                                const QString& file) {
    m_scanned = current;
    m_total = total;
    m_currentFile = file;
    emit progressChanged();
}

void ScanController::onFinished(const bool success, const QString& error) {
    m_running = false;

    if (success) {
        m_scanned = m_total;
        m_currentFile.clear();
    }

    if (!error.isEmpty())
        setError(error);

    emit runningChanged();
    emit progressChanged();
    emit finished(success);
}

void ScanController::onThreadFinished() {
    m_thread = nullptr;
    m_worker = nullptr;
}

void ScanController::resetState() {
    m_scanned = 0;
    m_total = 0;
    m_currentFile.clear();
    m_error.clear();

    emit progressChanged();
    emit errorChanged();
}

void ScanController::setError(const QString& error) {
    if (m_error == error)
        return;

    m_error = error;
    emit errorChanged();
}

} // namespace Track8::Gui

#include "ScanController.moc"
