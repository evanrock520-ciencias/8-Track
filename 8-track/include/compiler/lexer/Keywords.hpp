#pragma once
#include "TokenType.hpp"

#include <string>
#include <unordered_map>

namespace Track8::Compiler {

inline const std::unordered_map<std::string, TokenType> keywords = {
    {"and", TokenType::AND},         {"or", TokenType::OR},
    {"not", TokenType::NOT},         {"like", TokenType::LIKE},
    {"asc", TokenType::ASC},         {"desc", TokenType::DESC},
    {"by", TokenType::BY},           {"sort", TokenType::SORT},
    {"similar", TokenType::SIMILAR}, {"from", TokenType::FROM},
    {"to", TokenType::TO},           {"year", TokenType::YEAR},
    {"track", TokenType::TRACK},     {"performer", TokenType::PERFORMER},
    {"artist", TokenType::ARTIST},   {"band", TokenType::BAND},
    {"album", TokenType::ALBUM},     {"song", TokenType::SONG},
    {"member", TokenType::MEMBER},   {"path", TokenType::PATH}};

}