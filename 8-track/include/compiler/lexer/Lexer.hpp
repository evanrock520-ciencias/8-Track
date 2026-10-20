#pragma once
#include "Token.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace Track8::Compiler {

class Lexer {
public:
    explicit Lexer(std::string source);

    std::vector<Token> scanTokens();

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