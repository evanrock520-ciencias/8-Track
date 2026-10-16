#pragma once
#include <QtSql/QSqlDatabase>
#include <filesystem>

namespace Track8::Database {

/**
 * @class DatabaseManager
 * @brief Maneja la conexión con la base de datos.
 */
class DatabaseManager {
public:
    /**
     * @brief Accede o crea una base de datos para utilizar en el programa.
     * @param path La ruta de inicialización o creación de la base de datos.
     */
    explicit DatabaseManager(const std::filesystem::path& path);
    ~DatabaseManager();

    /**
     * @brief Cierra la conexión con la base de datos.
     */
    void shutdown();

    /**
     * Regresa una instancia de la base de datos.
     * @return una instancia de la base de datos.
     */
    [[nodiscard]] QSqlDatabase database() const { return m_database; }

private:
    void createTables();
    void insertDefaultSeeds();

    QSqlDatabase m_database;
    std::string m_connectionName;
};

} // namespace Track8::Database