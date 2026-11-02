#pragma once

#include <QObject>
#include <QString>
#include <QUrl>

#include <filesystem>

class QThread;

namespace Track8::Gui {

class ScanWorker;

/**
 * @class ScanController
 * @brief Controlador de la minera de archivos `.mp3`.
 */
class ScanController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool running READ running NOTIFY runningChanged)
    Q_PROPERTY(int scanned READ scanned NOTIFY progressChanged)
    Q_PROPERTY(int total READ total NOTIFY progressChanged)
    Q_PROPERTY(QString currentFile READ currentFile NOTIFY progressChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    explicit ScanController(std::filesystem::path dbPath,
                            std::filesystem::path coversDir,
                            QObject* parent = nullptr);
    ~ScanController() override;

    [[nodiscard]] bool running() const { return m_running; }
    [[nodiscard]] int scanned() const { return m_scanned; }
    [[nodiscard]] int total() const { return m_total; }
    [[nodiscard]] QString currentFile() const { return m_currentFile; }
    [[nodiscard]] QString error() const { return m_error; }

    /**
     * @brief Inicia el escaneo de un directorio en segundo plano.
     * @param directory URL local del directorio a escanear.
     */
    Q_INVOKABLE void start(const QUrl& directory);

signals:
    void runningChanged();
    void progressChanged();
    void errorChanged();
    void finished(bool success);

private slots:
    void onProgress(int current, int total, const QString& file);
    void onFinished(bool success, const QString& error);
    void onThreadFinished();

private:
    void resetState();
    void setError(const QString& error);

    std::filesystem::path m_dbPath;
    std::filesystem::path m_coversDir;

    QThread* m_thread = nullptr;
    ScanWorker* m_worker = nullptr;

    bool m_running = false;
    int m_scanned = 0;
    int m_total = 0;
    QString m_currentFile;
    QString m_error;
};

} // namespace Track8::Gui
