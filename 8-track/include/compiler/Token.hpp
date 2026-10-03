#pragma once
#include <string>

#include "TokenType.hpp"

namespace Track8::Compiler {
/**
 * @brief Representación de un token del DSL de consultas `MuQL`
 */
class Token {
public:
    Token(TokenType type, const std::string& lexeme, int line);

    [[nodiscard]] const TokenType& type() const { return m_type; }
    [[nodiscard]] const std::string& lexeme() const { return m_lexeme; }
    [[nodiscard]] int line() const { return m_line; }

private:
    const TokenType m_type;
    const std::string& m_lexeme;
    int m_line;
};
} // namespace Track8::Compiler
