#pragma once
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace Track8::Compiler::SQL {

using SqlValue = std::variant<std::string, int>;

struct SQLQuery {
    SQLQuery(std::string generated, std::vector<SqlValue> bindings)
        : generated(std::move(generated)), bindings(std::move(bindings)) {}

    std::string generated;
    std::vector<SqlValue> bindings;
};

} // namespace Track8::Compiler::SQL
