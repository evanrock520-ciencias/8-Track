#include <utility>

#include "compiler/lexer/Token.hpp"

namespace Track8::Compiler {
Token::Token(const TokenType type, std::string lexeme, const int line,
             std::any literal)
    : m_type(type),
      m_lexeme(std::move(lexeme)),
      m_line(line),
      m_literal(std::move(literal)) {}
} // namespace Track8::Compiler
