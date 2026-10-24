#pragma once

namespace Track8::Compiler {

enum class BinaryOperation { AND, OR };
enum class FilterField {
    PERFORMER,
    ARTIST,
    BAND,
    ALBUM,
    SONG,
    GENRE,
    MEMBER,
    PATH
};
enum class MatchMode { CONTAINS, EXACT, SIMILAR };
enum class SortField { ALBUM, SONG, PERFORMER, YEAR, TRACK, GENRE, PATH };
enum class SortOrder { ASC, DESC };

} // namespace Track8::Compiler