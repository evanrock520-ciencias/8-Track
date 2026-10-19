#include "database/DatabaseManager.hpp"

#include <QDir>
#include <QFile>
#include <QSqlQuery>
#include <iostream>

namespace Track8::Database {

DatabaseManager::DatabaseManager(const std::filesystem::path& path)
    : m_connectionName("eight_track") {
    m_database = QSqlDatabase::addDatabase(
        "QSQLITE", QString::fromStdString(m_connectionName));
    m_database.setDatabaseName(QString::fromStdString(path.string()));

    // En linux lo crea en ~/.local/share/8-track/8-track.db
    const QFileInfo info(QString::fromStdString(path.string()));
    QDir().mkpath(info.absolutePath());

    if (!m_database.open())
        throw std::runtime_error("Cannot open database");

    if (!isInitialized())
        createTables();

    QSqlQuery query(m_database);
    query.exec("PRAGMA foreign_keys = ON");
}

bool DatabaseManager::isInitialized() const {
    return m_database.tables().contains("rolas");
}

DatabaseManager::~DatabaseManager() {
    shutdown();
}

void DatabaseManager::createTables() const {
    std::cout << "Creating tables" << std::endl;
    QFile file(":/sql/rolas.sql");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Cannot open the SQL schema.");

    for (const QString script = QString::fromUtf8(file.readAll());
         const QString& sqlQuery : script.split(';', Qt::SkipEmptyParts)) {
        const QString sql = sqlQuery.trimmed();
        if (sql.isEmpty() || sql.startsWith("--"))
            continue;
        if (QSqlQuery query(m_database); !query.exec(sql))
            throw std::runtime_error("Cannot execute the SQL query.");
    }
}

void DatabaseManager::shutdown() {
    if (m_database.isOpen())
        m_database.close();

    m_database = QSqlDatabase();
    QSqlDatabase::removeDatabase(QString::fromStdString(m_connectionName));
}
} // namespace Track8::Database