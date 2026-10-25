#pragma once
#include "compiler/ast/IExpressionVisitor.hpp"
#include "compiler/ast/Query.hpp"
#include "compiler/transpiler/SQLQuery.hpp"

#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace Track8::Compiler::SQL {

class SQLTranspiler : public IExpressionVisitor {
public:
    [[nodiscard]] SQLQuery generate(const Query& query);

    void visit(const TemporalFilterNode& node) override;
    void visit(const TrackFilterNode& node) override;
    void visit(const NegationExpressionNode& node) override;
    void visit(const BinaryExpressionNode& node) override;
    void visit(const FreeFilterNode& node) override;
    void visit(const TextFilterNode& node) override;

private:
    void clear();
    static std::string resolveOperator(Compiler::MatchMode mode);
    void parenthesize(const IExpressionNode& node);
    void visitRange(std::string_view column, std::optional<int> from,
                    std::optional<int> to);

    std::string m_generated =
        "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
        "rolas.id_performer = performers.id_performer LEFT JOIN albums ON "
        "rolas.id_album = albums.id_album";
    std::vector<SqlValue> m_bindings;
};

} // namespace Track8::Compiler::SQL
