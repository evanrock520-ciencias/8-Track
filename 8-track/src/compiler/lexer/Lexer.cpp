#include "compiler/lexer/Lexer.hpp"

#include "compiler/lexer/Keywords.hpp"
#include "utils/Utils.hpp"

#include <stdexcept>
#include <utility>

namespace Track8::Compiler {

Lexer::Lexer(std::string source) : m_source(std::move(source)) {}

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        m_start = m_current;
        scanToken();
    }

    m_tokens.emplace_back(TokenType::END_OF_FILE, "", m_line, std::any{});
    return m_tokens;
}

void Lexer::scanToken() {
    switch (const char currentChar = advance()) {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        m_line++;
        break;

    case '"':
        string();
        break;

    case ':':
        addToken(match('=') ? TokenType::EXACTLY : TokenType::COLON);
        break;

    case '=':
        if (match('>')) {
            addToken(TokenType::RANGE);
            break;
        }

        throw std::runtime_error(std::to_string(m_line) +
                                 ": Unexpected character '='. Did you mean "
                                 "'=>'?");

    default:
        if (Utils::isDigit(currentChar))
            number();
        else if (Utils::isAlpha(currentChar))
            identifier();
        else
            throw std::runtime_error(std::to_string(m_line) +
                                     ": Unexpected character '" + currentChar +
                                     "'.");
        break;
    }
}

bool Lexer::isAtEnd() const {
    return m_current >= m_source.size();
}

char Lexer::advance() {
    return m_source[m_current++];
}

bool Lexer::match(const char expected) {
    if (isAtEnd())
        return false;
    if (m_source[m_current] != expected)
        return false;
    m_current++;
    return true;
}

char Lexer::peek() const {
    if (isAtEnd())
        return '\0';
    return m_source[m_current];
}

char Lexer::peekNext() const {
    if (m_current + 1 >= m_source.size())
        return '\0';
    return m_source[m_current + 1];
}

void Lexer::number() {
    while (Utils::isDigit(peek()))
        advance();

    // Solo enteros, no flotantes
    addToken(TokenType::NUMBER,
             std::stoi(m_source.substr(m_start, m_current - m_start)));
}

void Lexer::string() {
    const int startLine = m_line;
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            m_line++;
        advance();
    }

    if (isAtEnd())
        throw std::runtime_error(std::to_string(startLine) +
                                 ": Unterminated string.");

    advance();
    std::string value = m_source.substr(m_start + 1, m_current - m_start - 2);
    addToken(TokenType::STRING, value);
}

void Lexer::identifier() {
    while (Utils::isAlphaNumeric(peek()))
        advance();

    const std::string text = m_source.substr(m_start, m_current - m_start);

    auto type = TokenType::IDENTIFIER;
    if (const auto it = keywords.find(text); it != keywords.end())
        type = it->second;

    addToken(type);
}

void Lexer::addToken(const TokenType type) {
    addToken(type, std::any{});
}

void Lexer::addToken(const TokenType type, const std::any& literal) {
    const std::string text = m_source.substr(m_start, m_current - m_start);
    m_tokens.emplace_back(type, text, m_line, literal);
}

} // namespace Track8::Compiler