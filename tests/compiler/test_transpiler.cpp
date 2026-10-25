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
              "ON rolas.id_album = albums.id_album WHERE rolas.track = ?;");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<int>(binding), 3);
}

TEST(TranspilerTest, TranspilerTrackFilterTo) {
    const auto sqlQuery = sql(R"(track: => 5)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.track <= ?;");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<int>(binding), 5);
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

TEST(TranspilerTest, TranspilerTrackFilterEqualRange) {
    const auto sqlQuery = sql(R"(track: 3 => 3)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.track = ?;");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<int>(binding), 3);
}

TEST(TranspilerTest, TranspilerTemporalFilterFrom) {
    const auto sqlQuery = sql(R"(year: 1990)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.year = ?;");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<int>(binding), 1990);
}

TEST(TranspilerTest, TranspilerTemporalFilterTo) {
    const auto sqlQuery = sql(R"(year: => 2018)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.year <= ?;");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<int>(binding), 2018);
}

TEST(TranspilerTest, TranspilerTemporalFilterFromTo) {
    const auto sqlQuery = sql(R"(year: 2010 => 2018)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE rolas.year >= ? AND "
              "rolas.year <= ?;");

    const auto bindingFrom = sqlQuery.bindings.at(0);
    const auto bindingTo = sqlQuery.bindings.at(1);
    EXPECT_EQ(std::get<int>(bindingFrom), 2010);
    EXPECT_EQ(std::get<int>(bindingTo), 2018);
}

TEST(TranspilerTest, TranspilerNotFilter) {
    const auto sqlQuery = sql(R"(not album: "Pablo Honey")");
    EXPECT_EQ(
        sqlQuery.generated,
        "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
        "rolas.id_performer = performers.id_performer LEFT JOIN albums "
        "ON rolas.id_album = albums.id_album WHERE NOT (albums.name LIKE ?);");

    const auto binding = sqlQuery.bindings.at(0);
    EXPECT_EQ(std::get<std::string>(binding), "%Pablo Honey%");
}

TEST(TranspilerTest, TranspilerAndFilter) {
    const auto sqlQuery = sql(R"(album:= "Pet Sounds" and track: 5)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE (albums.name = ?) AND "
              "(rolas.track = ?);");

    const auto& albumBinding = sqlQuery.bindings.at(0);
    const auto& trackBinding = sqlQuery.bindings.at(1);
    EXPECT_EQ(std::get<std::string>(albumBinding), "Pet Sounds");
    EXPECT_EQ(std::get<int>(trackBinding), 5);
}

TEST(TranspilerTest, TranspilerOrFilter) {
    const auto sqlQuery = sql(R"(performer:= "The Zombies" or "Beach Boys")");
    EXPECT_EQ(
        sqlQuery.generated,
        "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
        "rolas.id_performer = performers.id_performer LEFT JOIN albums "
        "ON rolas.id_album = albums.id_album WHERE (performers.name = ?) OR "
        "(performers.name = ?);");

    const auto bindingLeft = sqlQuery.bindings.at(0);
    const auto bindingRight = sqlQuery.bindings.at(1);
    EXPECT_EQ(std::get<std::string>(bindingLeft), "The Zombies");
    EXPECT_EQ(std::get<std::string>(bindingRight), "Beach Boys");
}

TEST(TranspilerTest, TranspilerMember) {
    const auto sqlQuery = sql(R"(member: "Nico")");
    EXPECT_EQ(
        sqlQuery.generated,
        "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
        "rolas.id_performer = performers.id_performer LEFT JOIN albums "
        "ON rolas.id_album = albums.id_album WHERE performers.id_performer IN "
        "(SELECT ig.id_group FROM in_group ig JOIN persons person ON "
        "person.id_person = ig.id_person WHERE person.stage_name LIKE ?);");
}

TEST(TranspilerTest, TranspilerQueryWithSortClause) {
    const auto sqlQuery =
        sql(R"(performer:= "Weyes Blood" sort: desc by year)");
    EXPECT_EQ(sqlQuery.generated,
              "SELECT DISTINCT rolas.* FROM rolas LEFT JOIN performers ON "
              "rolas.id_performer = performers.id_performer LEFT JOIN albums "
              "ON rolas.id_album = albums.id_album WHERE performers.name = ? "
              "ORDER BY rolas.year DESC ;");
}