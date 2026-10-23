#include "compiler/ast/Nodes.hpp"

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

TEST(Ast, BinaryExpressionNode) {
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