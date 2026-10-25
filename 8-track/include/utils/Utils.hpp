#pragma once
#include "compiler/ast/Filters.hpp"
#include "compiler/lexer/TokenType.hpp"

#include <ranges>
#include <stdexcept>
#include <string>

namespace Track8::Utils {

/**
 * @brief Realiza el trabajo de `trim` en otros lenguajes de programación.
 * @param in La cadena de entrada.
 * @return Una cadena sin espacios iniciales.
 */
inline std::string trim(std::string in) {
    // Esto lo saqué de :
    // https://stackoverflow.com/questions/66897068/can-trim-of-a-string-be-done-inplace-with-c20-ranges
    auto view = std::views::all(in) | std::views::drop_while(isspace) |
                std::views::reverse | std::views::drop_while(isspace) |
                std::views::reverse;
    return std::string{view.begin(), view.end()};
}

/**
 * @brief Comprueba que una cadena es vacía tras aplicar un @ref trim.
 * @param str La cadena a comprobar si es vacía.
 * @return Si la cadena es vacía.
 */
inline bool empty(const std::string& str) {
    const std::string result = Utils::trim(str);
    return result.empty();
}

inline bool isDigit(const char expected) {
    return expected >= '0' && expected <= '9';
}

inline bool isAlpha(const char expected) {
    // Quizás expandir esto para el lenguaje.
    return expected >= 'a' && expected <= 'z' ||
           expected >= 'A' && expected <= 'Z' || expected == '_';
}

inline bool isAlphaNumeric(const char expected) {
    return isAlpha(expected) || isDigit(expected);
}

inline Compiler::FilterField toFilterField(const Compiler::TokenType type) {
    switch (type) {
    case Compiler::TokenType::PERFORMER:
        return Compiler::FilterField::PERFORMER;
    case Compiler::TokenType::ARTIST:
        return Compiler::FilterField::ARTIST;
    case Compiler::TokenType::BAND:
        return Compiler::FilterField::BAND;
    case Compiler::TokenType::ALBUM:
        return Compiler::FilterField::ALBUM;
    case Compiler::TokenType::SONG:
        return Compiler::FilterField::SONG;
    case Compiler::TokenType::GENRE:
        return Compiler::FilterField::GENRE;
    case Compiler::TokenType::MEMBER:
        return Compiler::FilterField::MEMBER;
    case Compiler::TokenType::PATH:
        return Compiler::FilterField::PATH;
    default:
        throw std::runtime_error("type with no filter field equivalent");
    }
}

inline bool startsRangeItem(const Compiler::TokenType type) {
    return type == Compiler::TokenType::NUMBER ||
           type == Compiler::TokenType::RANGE;
}

} // namespace Track8::Utils