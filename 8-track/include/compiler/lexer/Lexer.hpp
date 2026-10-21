#pragma once
#include "Token.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace Track8::Compiler {

/**
 * @class Lexer
 * @brief Escanea una cadena cruda (raw) para tokenizarla.
 */
class Lexer {
public:
    explicit Lexer(std::string source);

    /**
     * @brief Escanea la cadena @ref source para tokenizarla.
     * @return Un vector con los tokens de la cadena.
     */
    [[nodiscard]] std::vector<Token> scanTokens();

private:
    [[nodiscard]] bool isAtEnd() const;
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, const std::any& literal);
    bool match(char expected);
    [[nodiscard]] char peek() const;
    [[nodiscard]] char peekNext() const;

    void number();
    void identifier();
    void string();

    std::string m_source;
    std::vector<Token> m_tokens;
    int m_start = 0;
    int m_current = 0;
    int m_line = 1;
};

} // namespace Track8::Compiler