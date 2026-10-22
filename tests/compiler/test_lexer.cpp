#include "gtest/gtest.h"

#include "compiler/lexer/Lexer.hpp"

using namespace Track8;

TEST(LexerTest, EmptyString) {
    Compiler::Lexer lexer("");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 1); // Solo END_OF_FILE;
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::END_OF_FILE);
}

TEST(LexerTest, OnlyWhitespaces) {
    Compiler::Lexer lexer("\t \r \n");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::END_OF_FILE);
}

TEST(LexerTest, LexerString) {
    Compiler::Lexer lexer("\"Loveless\"");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokens.at(0).lexeme(), "\"Loveless\"");
    ASSERT_EQ(std::any_cast<std::string>(tokens.at(0).literal()), "Loveless");
}

TEST(LexerTest, LexerNumber) {
    Compiler::Lexer lexer("120");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::NUMBER);
    ASSERT_EQ(std::stoi(tokens.at(0).lexeme()), 120);
}

TEST(LexerTest, LexerOr) {
    Compiler::Lexer lexer(R"("Loveless" or "Black")");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens.at(1).type(), Compiler::TokenType::OR);
}

TEST(LexerTest, LexerAnd) {
    Compiler::Lexer lexer(R"("Loveless" and "Black")");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4); // STRING AND STRING
    ASSERT_EQ(tokens.at(1).type(), Compiler::TokenType::AND);
}

TEST(LexerTest, LexerNot) {
    Compiler::Lexer lexer(R"("Angel Olsen" not "The National")");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens.at(1).type(), Compiler::TokenType::NOT);
}

TEST(LexerTest, StringWithSimilarKeywordsPrefix) {
    Compiler::Lexer lexerAnd("andrea"); // and
    const auto tokensAnd = lexerAnd.scanTokens();
    ASSERT_EQ(tokensAnd.size(), 2);
    ASSERT_NE(tokensAnd.at(0).type(), Compiler::TokenType::AND);

    Compiler::Lexer lexerOr("ordinary"); // or
    const auto tokensOr = lexerOr.scanTokens();
    ASSERT_EQ(tokensOr.size(), 2);
    ASSERT_NE(tokensOr.at(0).type(), Compiler::TokenType::OR);

    Compiler::Lexer lexerNot("notice"); // not
    const auto tokensNot = lexerNot.scanTokens();
    ASSERT_EQ(tokensNot.size(), 2);
    ASSERT_NE(tokensNot.at(0).type(), Compiler::TokenType::NOT);
}

TEST(LexerTest, TwoCharactersTokens) {
    Compiler::Lexer lexerRange("=>");
    const auto tokens = lexerRange.scanTokens();
    ASSERT_EQ(tokens.size(), 2);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::RANGE);

    Compiler::Lexer lexerExactly(":=");
    const auto tokensExactly = lexerExactly.scanTokens();
    ASSERT_EQ(tokensExactly.size(), 2);
    ASSERT_EQ(tokensExactly.at(0).type(), Compiler::TokenType::EXACTLY);
}

TEST(LexerTest, SimpleQuery) {
    Compiler::Lexer lexer(R"(band: "The National")");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 4);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::BAND);
    ASSERT_EQ(tokens.at(1).type(), Compiler::TokenType::COLON);
    ASSERT_EQ(tokens.at(2).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokens.at(2).lexeme(), R"("The National")");
}

TEST(LexerTest, ComplexQuery) {
    Compiler::Lexer lexer(
        R"(artist: "Weyes Blood" and album: "Titanic Rising" and not song: "Andromeda")");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 13);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::ARTIST);
    ASSERT_EQ(tokens.at(1).type(), Compiler::TokenType::COLON);
    ASSERT_EQ(tokens.at(2).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokens.at(2).lexeme(), R"("Weyes Blood")");
    ASSERT_EQ(tokens.at(3).type(), Compiler::TokenType::AND);
    ASSERT_EQ(tokens.at(4).type(), Compiler::TokenType::ALBUM);
    ASSERT_EQ(tokens.at(5).type(), Compiler::TokenType::COLON);
    ASSERT_EQ(tokens.at(6).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokens.at(6).lexeme(), R"("Titanic Rising")");
    ASSERT_EQ(tokens.at(7).type(), Compiler::TokenType::AND);
    ASSERT_EQ(tokens.at(8).type(), Compiler::TokenType::NOT);
    ASSERT_EQ(tokens.at(9).type(), Compiler::TokenType::SONG);
    ASSERT_EQ(tokens.at(10).type(), Compiler::TokenType::COLON);
    ASSERT_EQ(tokens.at(11).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokens.at(11).lexeme(), R"("Andromeda")");
}

TEST(LexerTest, QueryUsingDoubleCharactersTokens) {
    Compiler::Lexer lexer(R"(artist: "Kaede" and year: 2000 =>)");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 9);
    ASSERT_EQ(tokens.at(0).type(), Compiler::TokenType::ARTIST);
    ASSERT_EQ(tokens.at(1).type(), Compiler::TokenType::COLON);
    ASSERT_EQ(tokens.at(2).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokens.at(2).lexeme(), R"("Kaede")");
    ASSERT_EQ(tokens.at(3).type(), Compiler::TokenType::AND);
    ASSERT_EQ(tokens.at(4).type(), Compiler::TokenType::YEAR);
    ASSERT_EQ(tokens.at(5).type(), Compiler::TokenType::COLON);
    ASSERT_EQ(tokens.at(6).type(), Compiler::TokenType::NUMBER);
    ASSERT_EQ(std::stoi(tokens.at(6).lexeme()), 2000);
    ASSERT_EQ(tokens.at(7).type(), Compiler::TokenType::RANGE);

    Compiler::Lexer lexerEquals(R"(band:= "Opeth")");
    const auto tokensEquals = lexerEquals.scanTokens();
    ASSERT_EQ(tokensEquals.size(), 4);
    ASSERT_EQ(tokensEquals.at(0).type(), Compiler::TokenType::BAND);
    ASSERT_EQ(tokensEquals.at(1).type(), Compiler::TokenType::EXACTLY);
    ASSERT_EQ(tokensEquals.at(2).type(), Compiler::TokenType::STRING);
    ASSERT_EQ(tokensEquals.at(2).lexeme(), R"("Opeth")");
}

TEST(LexerTest, NonClosedString) {
    Compiler::Lexer lexer(R"(band: "Vampire Weekend)");
    EXPECT_ANY_THROW(const auto tokens = lexer.scanTokens());
}

TEST(LexerTest, UnexpectedCharacters) {
    Compiler::Lexer lexerA("#");
    EXPECT_ANY_THROW(const auto tokensA = lexerA.scanTokens());

    Compiler::Lexer lexerB("@");
    EXPECT_ANY_THROW(const auto tokensB = lexerB.scanTokens());

    Compiler::Lexer lexerC("&");
    EXPECT_ANY_THROW(const auto tokensC = lexerC.scanTokens());

    Compiler::Lexer lexerD("|");
    EXPECT_ANY_THROW(const auto tokensD = lexerD.scanTokens());

    Compiler::Lexer lexerE("=");
    EXPECT_ANY_THROW(const auto tokensE = lexerE.scanTokens());
}

TEST(LexerTest, ExpectedLiteralValues) {
    Compiler::Lexer lexer(R"(artist: "Nico" and to: 1970)");
    const auto tokens = lexer.scanTokens();
    ASSERT_EQ(tokens.size(), 8);
    ASSERT_EQ(std::any_cast<std::string>(tokens.at(2).literal()), "Nico");
    ASSERT_EQ(std::any_cast<int>(tokens.at(6).literal()), 1970);
}