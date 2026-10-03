#include "compiler/Token.hpp"

namespace Track8::Compiler {
Token::Token(const TokenType type, const std::string& lexeme, const int line)
    : m_type(type), m_lexeme(lexeme), m_line(line) {}
} // namespace Track8::Compiler
