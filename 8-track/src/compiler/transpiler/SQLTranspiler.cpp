#include "compiler/transpiler/SQLTranspiler.hpp"

namespace Track8::Compiler::SQL {

SQLQuery SQLTranspiler::generate(const Query& query) {
    if (query.hasFilter()) {
        m_generated.append(" WHERE ");
        query.root()->accept(*this);
    }

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

void SQLTranspiler::visit(const TextFilterNode& node) {
    const auto mode = resolveOperator(node.mode());
    switch (node.type()) {
    case FilterField::SONG:
        m_generated.append("rolas.title " + mode + " ?");
        m_bindings.emplace_back(node.value());
        break;
    case FilterField::GENRE:
        m_generated.append("rolas.genre " + mode + " ?");
        m_bindings.emplace_back(node.value());
        break;
    case FilterField::PERFORMER:
        m_generated.append("performers.name " + mode + " ?");
        m_bindings.emplace_back(node.value());
        break;
    case FilterField::ARTIST:
        m_generated.append("performers.id_type = 0 AND ")
            .append("performers.name " + mode + " ?");
        m_bindings.emplace_back(node.value());
        break;
    case FilterField::BAND:
        m_generated.append("performers.id_type = 1 AND ")
            .append("performers.name " + mode + " ?");
        ;
        m_bindings.emplace_back(node.value());
        break;
    case FilterField::ALBUM:
        m_generated.append("albums.name " + mode + " ?");
        m_bindings.emplace_back(node.value());
        break;
    case FilterField::MEMBER:
        // TODO: Hacer otro JOIN en in_group
        break;
    case FilterField::PATH:
        m_generated.append("rolas.path " + mode + " ?");
        m_bindings.emplace_back(node.value());
        break;
    }
}

std::string SQLTranspiler::resolveOperator(const Compiler::MatchMode mode) {
    switch (mode) {
    case MatchMode::CONTAINS:
        return "LIKE";
    case MatchMode::EXACT:
        return "=";
    case MatchMode::SIMILAR:
        // TODO: Para este necesito fuzzy search, probablemente me robaré un
        // Levenshtein usado en SQLite
    default:
        throw std::runtime_error("Invalid match mode");
    }
}

} // namespace Track8::Compiler::SQL
