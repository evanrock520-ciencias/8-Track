#pragma once
#include "compiler/ast/Query.hpp"

namespace Track8::Compiler {

class QueryCompiler {
public:
    [[nodiscard]] static Query compile(std::string source);
};

} // namespace Track8::Compiler