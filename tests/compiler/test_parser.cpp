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