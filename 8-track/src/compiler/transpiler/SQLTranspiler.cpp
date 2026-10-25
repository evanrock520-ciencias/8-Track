#include "compiler/transpiler/SQLTranspiler.hpp"

namespace Track8::Compiler::SQL {

SQLQuery SQLTranspiler::generate(const Query& query) {
    clear();

    if (query.hasFilter()) {
        m_generated.append(" WHERE ");
        query.root()->accept(*this);
    }

    return {m_generated.append(";"), m_bindings};
}

void SQLTranspiler::clear() {
    m_generated =
        "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
        "rolas.id_performer = performers.id_performer LEFT JOIN albums ON "
        "rolas.id_album = albums.id_album";
    m_bindings.clear();
}

void SQLTranspiler::visit(const TemporalFilterNode& node) {
    visitRange("rolas.year", node.from(), node.to());
}

void SQLTranspiler::visit(const TrackFilterNode& node) {
    visitRange("rolas.track", node.from(), node.to());
}

void SQLTranspiler::visitRange(const std::string_view column,
                               const std::optional<int> from,
                               const std::optional<int> to) {
    if (from.has_value() && to.has_value() && from.value() == to.value()) {
        m_generated.append(column).append(" = ?");
        m_bindings.emplace_back(from.value());
        return;
    }

    if (from.has_value()) {
        m_generated.append(column).append(" >= ?");
        m_bindings.emplace_back(from.value());
    }

    if (to.has_value()) {
        if (from.has_value())
            m_generated.append(" AND ");
        m_generated.append(column).append(" <= ?");
        m_bindings.emplace_back(to.value());
    }
}

void SQLTranspiler::visit(const NegationExpressionNode& node) {
    m_generated.append("NOT ");
    parenthesize(node.expression());
}

void SQLTranspiler::visit(const BinaryExpressionNode& node) {
    parenthesize(node.left());
    m_generated.append(node.type() == BinaryOperation::AND ? " AND " : " OR ");
    parenthesize(node.right());
}

void SQLTranspiler::visit(const FreeFilterNode& node) {
    const std::string value = "%" + node.expression() + "%";

    m_generated.append("rolas.title LIKE ? OR rolas.genre LIKE ? OR "
                       "performers.name LIKE ? OR albums.name LIKE ?");
    m_bindings.emplace_back(value);
    m_bindings.emplace_back(value);
    m_bindings.emplace_back(value);
    m_bindings.emplace_back(value);
}

void SQLTranspiler::visit(const TextFilterNode& node) {
    const auto mode = resolveOperator(node.mode());
    const std::string value = (node.mode() == MatchMode::CONTAINS)
                                  ? "%" + node.value() + "%"
                                  : node.value();

    switch (node.type()) {
    case FilterField::SONG:
        m_generated.append("rolas.title " + mode + " ?");
        break;
    case FilterField::GENRE:
        m_generated.append("rolas.genre " + mode + " ?");
        break;
    case FilterField::PERFORMER:
        m_generated.append("performers.name " + mode + " ?");
        break;
    case FilterField::ARTIST:
        m_generated.append("performers.id_type = 0 AND ")
            .append("performers.name " + mode + " ?");
        break;
    case FilterField::BAND:
        m_generated.append("performers.id_type = 1 AND ")
            .append("performers.name " + mode + " ?");
        ;
        break;
    case FilterField::ALBUM:
        m_generated.append("albums.name " + mode + " ?");
        break;
    case FilterField::MEMBER:
        m_generated.append(
            "performers.id_performer IN (SELECT ig.id_group FROM in_group ig "
            "JOIN persons person ON person.id_person = ig.id_person WHERE "
            "person.stage_name " +
            mode + " ?)");
        break;
    case FilterField::PATH:
        m_generated.append("rolas.path " + mode + " ?");
        break;
    default:
        return;
    }
    m_bindings.emplace_back(value);
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

void SQLTranspiler::parenthesize(const IExpressionNode& node) {
    m_generated.append("(");
    node.accept(*this);
    m_generated.append(")");
}

} // namespace Track8::Compiler::SQL
