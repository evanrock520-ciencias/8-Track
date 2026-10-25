#pragma once

#include "compiler/transpiler/SQLQuery.hpp"

#include <string>

namespace Track8::Compiler {
class SQLCompiler {
public:
    [[nodiscard]] SQL::SQLQuery compile(std::string source) const;
};
} // namespace Track8::Compiler