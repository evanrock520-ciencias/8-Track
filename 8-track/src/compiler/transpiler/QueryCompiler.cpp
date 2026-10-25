#include "compiler/QueryCompiler.hpp"

#include "compiler/lexer/Lexer.hpp"
#include "compiler/parser/Parser.hpp"

namespace Track8::Compiler {

Query QueryCompiler::compile(std::string source) {
    Lexer lexer(std::move(source));
    Parser parser(lexer.scanTokens());
    return parser.parse();
}

} // namespace Track8::Compiler