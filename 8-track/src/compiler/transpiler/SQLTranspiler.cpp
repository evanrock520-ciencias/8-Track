#include "compiler/transpiler/SQLTranspiler.hpp"

namespace Track8::Compiler::SQL {

SQLQuery SQLTranspiler::generate(const Query& query) {
    if (query.hasFilter())
        query.root()->accept(*this);

    return {m_generated.append(";"), m_bindings};
}

void SQLTranspiler::visit(const TemporalFilterNode& node) {}

void SQLTranspiler::visit(const TrackFilterNode& node) {}

void SQLTranspiler::visit(const NegationExpressionNode& node) {}

void SQLTranspiler::visit(const BinaryExpressionNode& node) {}

void SQLTranspiler::visit(const FreeFilterNode& node) {
    m_generated.append("rolas.title LIKE ? OR rolas.genre LIKE ? OR "
                       "performers.name LIKE ? OR albums.name LIKE ?");
    m_bindings.emplace_back(node.expression());
    m_bindings.emplace_back(node.expression());
    m_bindings.emplace_back(node.expression());
    m_bindings.emplace_back(node.expression());
}

void SQLTranspiler::visit(const TextFilterNode& node) {}

} // namespace Track8::Compiler::SQL
