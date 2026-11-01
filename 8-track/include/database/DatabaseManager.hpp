#pragma once
#include "domain/repositories/ITransactionManager.hpp"

#include <QtSql/QSqlDatabase>
#include <filesystem>

namespace Track8::Database {

/**
 * @class DatabaseManager
 * @brief Maneja la conexión con la base de datos.
 */
class DatabaseManager : public Repositories::ITransactionManager {
public:
    /**
     * @brief Accede o crea una base de datos para utilizar en el programa.
     * @param path La ruta de inicialización o creación de la base de datos.
     */
    explicit DatabaseManager(const std::filesystem::path& path);
    ~DatabaseManager() override;

    /**
     * @brief Cierra la conexión con la base de datos.
     */
    void shutdown();

    /**
     * Regresa una instancia de la base de datos.
     * @return una instancia de la base de datos.
     */
    [[nodiscard]] QSqlDatabase database() const { return m_database; }

    /**
     * @brief Inicia una transacción en la base de datos SQLite.
     * @return true si la transacción fue iniciada, false en caso contrario.
     */
    bool transaction() override;

    /**
     * @brief Confirma la transacción actual.
     * @return true si se confirmó exitosamente, false en caso contrario.
     */
    bool commit() override;

    /**
     * @brief Revierte la transacción actual.
     * @return true si se revirtió exitosamente, false en caso contrario.
     */
    bool rollback() override;

private:
    /**
     * Ejecuta el script `rolas.sql` para crear las tablas de la base de datos.
     */
    void createTables() const;

    /**
     * Regresa si la tabla está inicializada.
     * @brief Revisa que la tabla `rolas` ha sido creada, considerando que es la
     * última definida en el script.
     * @return Si la tabla está inicializada.
     */
    bool isInitialized() const;

    QSqlDatabase m_database;
    std::string m_connectionName;
};

} // namespace Track8::Database