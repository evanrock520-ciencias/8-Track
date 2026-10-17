#include "database/DatabaseManager.hpp"

#include <QFile>
#include <QSqlQuery>
#include <iostream>

namespace Track8::Database {

DatabaseManager::DatabaseManager(const std::filesystem::path& path)
    : m_connectionName(path) {
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QString::fromStdString(m_connectionName));
    m_database = database;
    if (!database.open())
        throw std::runtime_error("Cannot open database");

    if (!isInitialized())
        createTables();
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