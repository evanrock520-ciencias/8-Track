#pragma once

namespace Track8::Repositories {

/**
 * @class ITransactionManager
 * @brief Interfaz para el control de transacciones en la capa de persistencia.
 */
class ITransactionManager {
public:
    virtual ~ITransactionManager() = default;

    /**
     * @brief Inicia una transacción en la base de datos.
     * @return true si la transacción se inició exitosamente, false en caso
     * contrario.
     */
    virtual bool transaction() = 0;

    /**
     * @brief Confirma los cambios realizados durante la transacción.
     * @return true si la confirmación fue exitosa, false en caso contrario.
     */
    virtual bool commit() = 0;

    /**
     * @brief Revierte los cambios realizados durante la transacción.
     * @return true si la reversión fue exitosa, false en caso contrario.
     */
    virtual bool rollback() = 0;
};

} // namespace Track8::Repositories
