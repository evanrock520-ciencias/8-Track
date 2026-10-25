#pragma once

namespace Track8::Compiler {

/**
 * @brief Representa los tokens posibles para el DSL de consultas `MuQL`.
 */
enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,

    // One or two character tokens.
    EXACTLY, // :=
    RANGE,   // =>

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    NOT,
    OR,
    LIKE,
    ASC,
    DESC,
    BY,
    SORT,
    SIMILAR,
    FROM,
    TO,
    YEAR,
    TRACK,
    PERFORMER,
    ARTIST,
    BAND,
    ALBUM,
    SONG,
    GENRE,
    MEMBER,
    PATH,

    END_OF_FILE
};

[[nodiscard]] constexpr bool isTextField(const TokenType token) noexcept {
    switch (token) {
    case TokenType::PERFORMER:
    case TokenType::ARTIST:
    case TokenType::BAND:
    case TokenType::ALBUM:
    case TokenType::SONG:
    case TokenType::GENRE:
    case TokenType::MEMBER:
    case TokenType::PATH:
        return true;
    default:
        return false;
    }
}

[[nodiscard]] constexpr bool isTemporalField(const TokenType token) noexcept {
    switch (token) {
    case TokenType::TO:
    case TokenType::YEAR:
    case TokenType::FROM:
        return true;
    default:
        return false;
    }
}
[[nodiscard]] constexpr bool isSimilarField(const TokenType token) noexcept {
    switch (token) {
    case TokenType::SONG:
    case TokenType::PERFORMER:
    case TokenType::ALBUM:
    case TokenType::GENRE:
        return true;
    default:
        return false;
    }
}

[[nodiscard]] constexpr bool isSortKey(const TokenType token) noexcept {
    switch (token) {
    case TokenType::SONG:
    case TokenType::PERFORMER:
    case TokenType::ALBUM:
    case TokenType::YEAR:
    case TokenType::TRACK:
    case TokenType::GENRE:
    case TokenType::PATH:
        return true;
    default:
        return false;
    }
}

[[nodiscard]] constexpr bool isValue(const TokenType type) noexcept {
    return type == TokenType::STRING || type == TokenType::IDENTIFIER;
}

} // namespace Track8::Compiler
