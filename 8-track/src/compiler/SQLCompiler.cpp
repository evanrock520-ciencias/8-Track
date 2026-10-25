#include "compiler/SQLCompiler.hpp"
#include "compiler/lexer/Lexer.hpp"
#include "compiler/parser/Parser.hpp"
#include "compiler/transpiler/SQLTranspiler.hpp"

#include <utility>

namespace Track8::Compiler {

SQL::SQLQuery SQLCompiler::compile(std::string source) const {
    Lexer lexer(std::move(source));
    Parser parser(lexer.scanTokens());

    SQL::SQLTranspiler transpiler;
    return transpiler.generate(parser.parse());
}

} // namespace Track8::Compiler