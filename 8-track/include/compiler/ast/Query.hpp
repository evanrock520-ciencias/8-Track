#pragma once

#include "compiler/ast/Nodes.hpp"
#include "compiler/ast/SortClause.hpp"

#include <memory>
#include <optional>
#include <utility>

namespace Track8::Compiler {

/**
 * @class Query
 * @brief Representa una consulta MuQL usando un AST.
 */
class Query {
public:
    explicit Query(std::unique_ptr<IExpressionNode> root = nullptr,
                   std::optional<SortClause> sortClause = std::nullopt)
        : m_root(std::move(root)), m_sortClause(std::move(sortClause)) {}

    /**
     * Determina si la `query` contiene un filtro.
     * @return Si la `query` contiene un filtro.
     */
    [[nodiscard]] bool hasFilter() const { return m_root != nullptr; }

    /**
     * Determina si la `query` contiene una clausula de ordenamiento.
     * @return Si la `query` contiene una clausula de ordenamiento.
     */
    [[nodiscard]] bool hasSort() const { return m_sortClause.has_value(); }

    /**
     * Regresa la raíz del árbol AST.
     * @return La raíz del árbol AST.
     */
    [[nodiscard]] const IExpressionNode* root() const { return m_root.get(); }

    /**
     * Regresa la clausula de ordenamiento.
     * @return La clausula de ordenamiento.
     */
    [[nodiscard]] const SortClause* sortClause() const {
        return m_sortClause ? &*m_sortClause : nullptr;
    }

private:
    std::unique_ptr<IExpressionNode> m_root;
    std::optional<SortClause> m_sortClause;
};

} // namespace Track8::Compiler
