#include "compiler/ast/AstPrinter.hpp"
#include "compiler/ast/Nodes.hpp"
#include "compiler/ast/Query.hpp"

#include "gtest/gtest.h"

using namespace Track8::Compiler;

TEST(AstTest, FreeFilterNode) {
    const FreeFilterNode node("The Residents");
    ASSERT_EQ("The Residents", node.expression());
}

TEST(AstTest, TemporalFilterNode) {
    const TemporalFilterNode nodeA(1965, 1970);
    ASSERT_EQ(nodeA.from(), 1965);
    ASSERT_EQ(nodeA.to(), 1970);

    const TemporalFilterNode nodeB(1990, std::nullopt);
    ASSERT_EQ(nodeB.from(), 1990);
    ASSERT_TRUE(!nodeB.to().has_value());

    const TemporalFilterNode nodeC(std::nullopt, 2000);
    ASSERT_TRUE(!nodeC.from().has_value());
    ASSERT_EQ(nodeC.to(), 2000);
}

TEST(AstTest, TrackFilterNode) {
    const TrackFilterNode node(1965, 1970);
    ASSERT_EQ(node.from(), 1965);
    ASSERT_EQ(node.to(), 1970);

    const TrackFilterNode nodeB(1990, std::nullopt);
    ASSERT_EQ(nodeB.from(), 1990);
    ASSERT_TRUE(!nodeB.to().has_value());

    const TrackFilterNode nodeC(std::nullopt, 2000);
    ASSERT_TRUE(!nodeC.from().has_value());
    ASSERT_EQ(nodeC.to(), 2000);
}

TEST(AstTest, TextFilterNode) {
    const TextFilterNode node(FilterField::ALBUM,
                              "Burn Your Fire With No Witness",
                              MatchMode::SIMILAR);
    ASSERT_EQ(node.type(), FilterField::ALBUM);
    ASSERT_EQ(node.value(), "Burn Your Fire With No Witness");
    ASSERT_EQ(node.mode(), MatchMode::SIMILAR);
}

TEST(AstTest, NegationExpressionNode) {
    auto temporalNode = std::make_unique<TemporalFilterNode>(2020, 2025);
    const NegationExpressionNode node(std::move(temporalNode));

    const auto& savedNode =
        dynamic_cast<const TemporalFilterNode&>(node.expression());
    ASSERT_EQ(savedNode.from(), 2020);
    ASSERT_EQ(savedNode.to(), 2025);
}

TEST(AstTest, BinaryExpressionNode) {
    auto temporalNode = std::make_unique<TemporalFilterNode>(1965, 1970);
    auto albumNode = std::make_unique<TextFilterNode>(
        FilterField::ALBUM, "Sunflower", MatchMode::SIMILAR);
    const BinaryExpressionNode node(BinaryOperation::AND, std::move(albumNode),
                                    std::move(temporalNode));

    const auto& albumSaved = dynamic_cast<const TextFilterNode&>(node.left());
    const auto& temporalSaved =
        dynamic_cast<const TemporalFilterNode&>(node.right());

    ASSERT_EQ(temporalSaved.from(), 1965);
    ASSERT_EQ(temporalSaved.to(), 1970);
    ASSERT_EQ(albumSaved.type(), FilterField::ALBUM);
    ASSERT_EQ(albumSaved.value(), "Sunflower");
    ASSERT_EQ(albumSaved.mode(), MatchMode::SIMILAR);
}

TEST(AstTest, QueryGetters) {
    auto temporalNode = std::make_unique<TemporalFilterNode>(1965, 1970);
    SortClause clause(SortOrder::DESC, SortField::SONG);

    const Query query(std::move(temporalNode), clause);
    const auto temporalQuery =
        dynamic_cast<const TemporalFilterNode&>(*query.root());
    const auto clauseQuery = query.sortClause();
    ASSERT_EQ(temporalQuery.from(), 1965);
    ASSERT_EQ(temporalQuery.to(), 1970);
    ASSERT_EQ(clauseQuery->order(), SortOrder::DESC);
    ASSERT_EQ(clauseQuery->field(), SortField::SONG);
}

TEST(AstTest, AstPrinterTextFilter) {
    AstPrinter printer;

    const TextFilterNode containsNode(FilterField::ARTIST, "Lana del Rey",
                                      MatchMode::CONTAINS);
    EXPECT_EQ(printer.print(containsNode), "(artist: \"Lana del Rey\")");

    const TextFilterNode exactNode(FilterField::BAND, "Opeth",
                                   MatchMode::EXACT);
    EXPECT_EQ(printer.print(exactNode), "(band:= \"Opeth\")");

    const TextFilterNode similarNode(FilterField::SONG, "Black",
                                     MatchMode::SIMILAR);
    EXPECT_EQ(printer.print(similarNode), "(similar: song like \"Black\")");
}

TEST(AstTest, AstPrinterTemporalAndTrackFilter) {
    AstPrinter printer;

    const TemporalFilterNode yearRange(1965, 1970);
    EXPECT_EQ(printer.print(yearRange), "(year: 1965 => 1970)");

    const TemporalFilterNode singleYear(2020, 2020);
    EXPECT_EQ(printer.print(singleYear), "(year: 2020)");

    const TemporalFilterNode yearFrom(2010, std::nullopt);
    EXPECT_EQ(printer.print(yearFrom), "(year: 2010 =>)");

    const TrackFilterNode trackRange(1, 5);
    EXPECT_EQ(printer.print(trackRange), "(track: 1 => 5)");
}

TEST(AstTest, AstPrinterFreeFilter) {
    AstPrinter printer;
    const FreeFilterNode freeNode("White Lies");
    EXPECT_EQ(printer.print(freeNode), "\"White Lies\"");
}

TEST(AstTest, AstPrinterNegation) {
    AstPrinter printer;
    auto yearNode = std::make_unique<TemporalFilterNode>(1990, 1999);
    const NegationExpressionNode notNode(std::move(yearNode));

    EXPECT_EQ(printer.print(notNode), "(NOT (year: 1990 => 1999))");
}

TEST(AstTest, AstPrinterBinary) {
    AstPrinter printer;
    auto left = std::make_unique<TextFilterNode>(
        FilterField::ARTIST, "Alexandra Savior", MatchMode::CONTAINS);
    auto right = std::make_unique<TextFilterNode>(
        FilterField::ARTIST, "Miles Kane", MatchMode::CONTAINS);

    const BinaryExpressionNode orNode(BinaryOperation::OR, std::move(left),
                                      std::move(right));
    EXPECT_EQ(printer.print(orNode),
              "(OR (artist: \"Alexandra Savior\") (artist: \"Miles Kane\"))");
}

TEST(AstTest, AstPrinterComplexTree) {
    AstPrinter printer;

    auto performer = std::make_unique<TextFilterNode>(
        FilterField::PERFORMER, "Angel Olsen", MatchMode::CONTAINS);
    auto album = std::make_unique<TextFilterNode>(
        FilterField::ALBUM, "All Mirrors", MatchMode::CONTAINS);
    auto leftAnd = std::make_unique<BinaryExpressionNode>(
        BinaryOperation::AND, std::move(performer), std::move(album));

    auto song = std::make_unique<TextFilterNode>(FilterField::SONG, "Lark",
                                                 MatchMode::CONTAINS);
    auto notSong = std::make_unique<NegationExpressionNode>(std::move(song));

    const BinaryExpressionNode root(BinaryOperation::AND, std::move(leftAnd),
                                    std::move(notSong));

    EXPECT_EQ(printer.print(root),
              "(AND (AND (performer: \"Angel Olsen\") (album: \"All "
              "Mirrors\")) (NOT (song: \"Lark\")))");
}