#include "compiler/lexer/Lexer.hpp"
#include "compiler/parser/Parser.hpp"
#include "compiler/transpiler/SQLTranspiler.hpp"

#include "gtest/gtest.h"

using namespace Track8::Compiler;
using namespace Track8::Compiler::SQL;

static inline SQLQuery sql(std::string value) {
    Lexer lexer(std::move(value));
    Parser parser(lexer.scanTokens());
    SQLTranspiler transpiler;
    return transpiler.generate(parser.parse());
}

TEST(TranspilerTest, TranspilerFreeFilter) {
    const auto sqlQuery = sql(R"("Love")");
    EXPECT_EQ(
        sqlQuery.generated,
        "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
        "rolas.id_performer = performers.id_performer LEFT JOIN albums ON "
        "rolas.id_album = albums.id_album WHERE rolas.title LIKE ? OR "
        "rolas.genre LIKE ? OR performers.name LIKE ? OR albums.name LIKE ?;");
    for (const auto& binding : sqlQuery.bindings)
        EXPECT_EQ(std::get<std::string>(binding), "%Love%");
}

TEST(TranspilerTest, TranspilerTextFilterContains) {
    const auto sqlQuery = sql(R"(song: "Anger Never Dies")");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.title LIKE ?;");
    const auto& binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<std::string>(binding), "%Anger Never Dies%");
}

TEST(TranspilerTest, TranspilerTextFilterExactly) {
    const auto sqlQuery = sql(R"(song:= "Anger Never Dies")");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.title = ?;");
    const auto& binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<std::string>(binding), "Anger Never Dies");
}

TEST(TranspilerTest, TranspilerTrackFilter) {
    const auto sqlQuery = sql(R"(track: 3)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.track >= ?;");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<int>(binding), 3);
}

TEST(TranspilerTest, TranspilerTrackFilterRange) {
    const auto sqlQuery = sql(R"(track: 3 => 6)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.track >= ? AND "
              "rolas.track <= ?;");

    const auto& bindingFrom = sqlQuery.bindings.at(0);
    const auto& bindingTo = sqlQuery.bindings.at(1);

    EXPECT_EQ(std::get<int>(bindingFrom), 3);
    EXPECT_EQ(std::get<int>(bindingTo), 6);
}