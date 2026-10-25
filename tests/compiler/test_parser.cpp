#include "gtest/gtest.h"

#include "compiler/ast/AstPrinter.hpp"
#include "compiler/ast/Query.hpp"
#include "compiler/lexer/Lexer.hpp"
#include "compiler/parser/Parser.hpp"

#include <iostream>

using namespace Track8::Compiler;

TEST(ParserTest, TextFilterContains) {
    Lexer lexer(R"(artist: "Julee Cruise")");
    Parser parser(lexer.scanTokens());

    const auto query = parser.parse();
    ASSERT_TRUE(query.hasFilter());

    const auto* root = query.root();
    ASSERT_EQ(typeid(*root), typeid(TextFilterNode));
    const auto* node = dynamic_cast<const TextFilterNode*>(root);
    ASSERT_EQ(node->type(), FilterField::ARTIST);
    ASSERT_EQ(node->value(), "Julee Cruise");
    ASSERT_EQ(node->mode(), MatchMode::CONTAINS);
}

TEST(ParserTest, TextFilterExactly) {
    Lexer lexer(R"(band:= "Men I Trust")");
    Parser parser(lexer.scanTokens());

    const auto query = parser.parse();
    ASSERT_TRUE(query.hasFilter());

    const auto* root = query.root();
    ASSERT_EQ(typeid(*root), typeid(TextFilterNode));
    const auto* node = dynamic_cast<const TextFilterNode*>(root);
    ASSERT_EQ(node->type(), FilterField::BAND);
    ASSERT_EQ(node->value(), "Men I Trust");
    ASSERT_EQ(node->mode(), MatchMode::EXACT);
}

TEST(ParserTest, TemporalFilterFrom) {
    Lexer lexer(R"(from: 2020)");
    Parser parser(lexer.scanTokens());

    const auto query = parser.parse();
    ASSERT_TRUE(query.hasFilter());

    const auto* root = query.root();
    ASSERT_EQ(typeid(*root), typeid(TemporalFilterNode));
    const auto* node = dynamic_cast<const TemporalFilterNode*>(root);
    ASSERT_EQ(node->from(), 2020);
    ASSERT_FALSE(node->to().has_value());
}

TEST(ParserTest, TemporalFilterTo) {
    Lexer lexer(R"(to: 1985)");
    Parser parser(lexer.scanTokens());

    const auto query = parser.parse();
    ASSERT_TRUE(query.hasFilter());

    const auto* root = query.root();
    ASSERT_EQ(typeid(*root), typeid(TemporalFilterNode));
    const auto* node = dynamic_cast<const TemporalFilterNode*>(root);
    ASSERT_EQ(node->to(), 1985);
    ASSERT_FALSE(node->from().has_value());
}

TEST(ParserTest, TemporalFilterWithYear) {
    Lexer lexerA(R"(year: 2020)");
    Parser parserA(lexerA.scanTokens());

    const auto queryA = parserA.parse();
    ASSERT_TRUE(queryA.hasFilter());

    const auto* rootA = queryA.root();
    ASSERT_EQ(typeid(*rootA), typeid(TemporalFilterNode));
    const auto* nodeA = dynamic_cast<const TemporalFilterNode*>(rootA);
    ASSERT_EQ(nodeA->from(), 2020);
    ASSERT_EQ(nodeA->to(), 2020);

    Lexer lexerB(R"(year: => 1990)");
    Parser parserB(lexerB.scanTokens());

    const auto queryB = parserB.parse();
    ASSERT_TRUE(queryB.hasFilter());

    const auto* rootB = queryB.root();
    ASSERT_EQ(typeid(*rootB), typeid(TemporalFilterNode));
    const auto* nodeB = dynamic_cast<const TemporalFilterNode*>(rootB);
    ASSERT_EQ(nodeB->to(), 1990);
    ASSERT_FALSE(nodeB->from().has_value());

    Lexer lexerC(R"(year: 1967 =>)");
    Parser parserC(lexerC.scanTokens());

    const auto queryC = parserC.parse();
    ASSERT_TRUE(queryC.hasFilter());

    const auto* rootC = queryC.root();
    ASSERT_EQ(typeid(*rootC), typeid(TemporalFilterNode));
    const auto* nodeC = dynamic_cast<const TemporalFilterNode*>(rootC);
    ASSERT_EQ(nodeC->from(), 1967);
    ASSERT_FALSE(nodeC->to().has_value());

    Lexer lexerD(R"(year: 2000 => 2010)");
    Parser parserD(lexerD.scanTokens());

    const auto queryD = parserD.parse();
    ASSERT_TRUE(queryD.hasFilter());

    const auto* rootD = queryD.root();
    ASSERT_EQ(typeid(*rootD), typeid(TemporalFilterNode));
    const auto* nodeD = dynamic_cast<const TemporalFilterNode*>(rootD);
    ASSERT_EQ(nodeD->from(), 2000);
    ASSERT_EQ(nodeD->to(), 2010);
}