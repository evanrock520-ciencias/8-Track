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