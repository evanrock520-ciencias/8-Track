#pragma once
#include "compiler/ast/Filters.hpp"

namespace Track8::Compiler {

/**
 * @struct SortClause
 * @brief Representa una clausula que determina el orden para obtener una tabla.
 */
struct SortClause {
    SortClause(const SortOrder order, const SortField field)
        : m_order(order), m_field(field) {}

    /**
     * Regresa el orden de la clausula.
     * @return El orden de la clausula.
     */
    [[nodiscard]] SortOrder order() const { return m_order; }

    /**
     * Regresa el campo ordenado.
     * @return El campo ordenado.
     */
    [[nodiscard]] SortField field() const { return m_field; }

private:
    SortOrder m_order;
    SortField m_field;
};

} // namespace Track8::Compiler