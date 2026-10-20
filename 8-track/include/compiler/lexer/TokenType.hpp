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
} // namespace Track8::Compiler
