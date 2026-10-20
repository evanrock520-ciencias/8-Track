#pragma once
#include <string>

#include "TokenType.hpp"

#include <any>

namespace Track8::Compiler {
/**
 * @brief Representación de un token del DSL de consultas `MuQL`
 */
class Token {
public:
    Token(TokenType type, std::string lexeme, int line, std::any literal);

    [[nodiscard]] const TokenType& type() const { return m_type; }
    [[nodiscard]] const std::string& lexeme() const { return m_lexeme; }
    [[nodiscard]] int line() const { return m_line; }

private:
    TokenType m_type;
    std::string m_lexeme;
    int m_line;
    std::any m_literal;
};
} // namespace Track8::Compiler
