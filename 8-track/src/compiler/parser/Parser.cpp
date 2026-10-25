#include "compiler/parser/Parser.hpp"

#include "compiler/ast/Nodes.hpp"
#include "utils/Utils.hpp"

#include <algorithm>
#include <any>
#include <stdexcept>
#include <string>

namespace Track8::Compiler {

Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens) {}

Query Parser::parse() {
    std::unique_ptr<IExpressionNode> root;
    if (!isAtEnd() && !check(TokenType::SORT))
        root = expression();

    std::optional<SortClause> sort;
    if (check(TokenType::SORT))
        sort = sortClause();

    if (!isAtEnd())
        fail("expected end of input");

    return Query(std::move(root), sort);
}

std::unique_ptr<IExpressionNode> Parser::expression() {
    return orExpression();
}

std::unique_ptr<IExpressionNode> Parser::orExpression() {
    auto expr = andExpression();

    while (match(TokenType::OR)) {
        auto right = andExpression();
        expr = std::make_unique<BinaryExpressionNode>(
            BinaryOperation::OR, std::move(expr), std::move(right));
    }

    return expr;
}

std::unique_ptr<IExpressionNode> Parser::andExpression() {
    auto expr = notExpression();

    while (check(TokenType::AND) || startsNot()) {
        match(TokenType::AND);
        auto right = notExpression();
        expr = std::make_unique<BinaryExpressionNode>(
            BinaryOperation::AND, std::move(expr), std::move(right));
    }

    return expr;
}

std::unique_ptr<IExpressionNode> Parser::notExpression() {
    if (match(TokenType::NOT)) {
        auto operand = notExpression();
        return std::make_unique<NegationExpressionNode>(std::move(operand));
    }

    return primary();
}

std::unique_ptr<IExpressionNode> Parser::primary() {
    if (match(TokenType::LEFT_PAREN)) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "expected ')' after expression");
        return expr;
    }

    if (isFilterStart())
        return filter();

    return term();
}

std::unique_ptr<IExpressionNode> Parser::term() {
    std::vector<std::unique_ptr<IExpressionNode>> nodes;
    for (auto& value : values())
        nodes.push_back(std::make_unique<FreeFilterNode>(std::move(value)));
    return orAll(std::move(nodes));
}

std::unique_ptr<IExpressionNode> Parser::filter() {
    const TokenType type = peek().type();

    if (isTextField(type))
        return textFilter();

    if (isTemporalField(type))
        return temporalFilter();

    if (type == TokenType::TRACK)
        return trackFilter();

    if (type == TokenType::SIMILAR)
        return similarFilter();

    fail("unexpected filter type");
}

std::unique_ptr<IExpressionNode> Parser::textFilter() {
    const Token& fieldToken = advance();
    const FilterField field = Utils::toFilterField(fieldToken.type());

    MatchMode mode;
    if (match(TokenType::COLON))
        mode = MatchMode::CONTAINS;
    else if (match(TokenType::EXACTLY))
        mode = MatchMode::EXACT;
    else
        fail("expected ':' or ':=' as match mode");

    std::vector<std::unique_ptr<IExpressionNode>> nodes;
    for (auto& value : values())
        nodes.push_back(
            std::make_unique<TextFilterNode>(field, std::move(value), mode));

    return orAll(std::move(nodes));
}

std::unique_ptr<IExpressionNode> Parser::similarFilter() {
    consume(TokenType::SIMILAR, "expected 'similar' keyword");
    consume(TokenType::COLON, "expected ':' after 'similar' keyword");

    const Token& fieldToken = peek();
    if (!isSimilarField(fieldToken.type()))
        fail("expected a similar field ('song', 'performer', 'album' or "
             "'genre')");
    advance();
    const FilterField field = Utils::toFilterField(fieldToken.type());

    consume(TokenType::LIKE, "expected 'like' after a similar field");
    const auto val = value();
    return std::make_unique<TextFilterNode>(field, val, MatchMode::SIMILAR);
}

std::unique_ptr<IExpressionNode> Parser::trackFilter() {
    consume(TokenType::TRACK, "expected 'track' keyword");
    consume(TokenType::COLON, "expected ':' after track keyword");

    std::vector<std::unique_ptr<IExpressionNode>> nodes;
    for (const Domain::Range& range : rangeList())
        nodes.push_back(
            std::make_unique<TrackFilterNode>(range.from, range.to));
    return orAll(std::move(nodes));
}

std::unique_ptr<IExpressionNode> Parser::temporalFilter() {
    const TokenType keyword = advance().type();
    consume(TokenType::COLON, "expected ':' after keyword");

    if (keyword == TokenType::YEAR) {
        std::vector<std::unique_ptr<IExpressionNode>> nodes;
        for (const Domain::Range& range : rangeList())
            nodes.push_back(
                std::make_unique<TemporalFilterNode>(range.from, range.to));
        return orAll(std::move(nodes));
    }

    const int value = integer();
    if (keyword == TokenType::FROM)
        return std::make_unique<TemporalFilterNode>(value, std::nullopt);
    return std::make_unique<TemporalFilterNode>(std::nullopt, value);
}

std::unique_ptr<IExpressionNode>
Parser::orAll(std::vector<std::unique_ptr<IExpressionNode>> nodes) {
    auto result = std::move(nodes.front());
    for (std::size_t i = 1; i < nodes.size(); ++i) {
        result = std::make_unique<BinaryExpressionNode>(
            BinaryOperation::OR, std::move(result), std::move(nodes[i]));
    }
    return result;
}

int Parser::integer() {
    const Token& token = consume(TokenType::NUMBER, "expected an integer");
    return std::any_cast<int>(token.literal());
}

std::vector<Domain::Range> Parser::rangeList() {
    std::vector<Domain::Range> ranges;
    ranges.push_back(rangeItem());

    while (check(TokenType::OR) && Utils::startsRangeItem(peek(1).type())) {
        advance();
        ranges.push_back(rangeItem());
    }
    return ranges;
}

Domain::Range Parser::rangeItem() {
    if (match(TokenType::RANGE))
        return {std::nullopt, integer()};

    const int from = integer();
    if (!match(TokenType::RANGE))
        return {from, from};
    if (check(TokenType::NUMBER))
        return {from, integer()};
    return {from, std::nullopt};
}

const Token& Parser::peek(const std::size_t offset) const {
    const std::size_t index = std::min(m_current + offset, m_tokens.size() - 1);
    return m_tokens[index];
}

const Token& Parser::previous() const {
    return m_tokens[m_current - 1];
}

bool Parser::check(const TokenType type) const {
    return peek().type() == type;
}

bool Parser::isAtEnd() const {
    return peek().type() == TokenType::END_OF_FILE;
}

bool Parser::match(const std::initializer_list<TokenType> types) {
    for (const auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

bool Parser::match(const TokenType type) {
    return match({type});
}

const Token& Parser::advance() {
    const Token& token = peek();
    if (!isAtEnd())
        m_current++;
    return token;
}

const Token& Parser::consume(const TokenType type,
                             const std::string_view message) {
    if (check(type))
        return advance();

    fail(message);
}

std::string Parser::value() {
    const Token& token = peek();

    if (token.type() == TokenType::STRING) {
        advance();
        return std::any_cast<std::string>(token.literal());
    }

    if (token.type() == TokenType::IDENTIFIER) {
        advance();
        return token.lexeme();
    }

    fail("unexpected value");
}

std::vector<std::string> Parser::values() {
    std::vector<std::string> values;
    values.push_back(value());

    while (check(TokenType::OR) && isValue(peek(1).type())) {
        advance();
        values.push_back(value());
    }
    return values;
}

std::optional<SortClause> Parser::sortClause() {
    consume(TokenType::SORT, "expected the 'sort' keyword");
    consume(TokenType::COLON, "expected ':' after 'sort' keyword");

    auto order = SortOrder::ASC;
    if (match({TokenType::ASC, TokenType::DESC}))
        order = Utils::toSortOrder(previous().type());

    consume(TokenType::BY, "expected 'by' in sort clause");

    if (!isSortKey(peek().type()))
        fail("expected a sort key ('song', 'performer', 'album', 'year', "
             "'track', 'genre', 'path')");

    const SortField field = Utils::toSortField(advance().type());
    return SortClause(order, field);
}

bool Parser::isFilterStart() const {
    const TokenType type = peek().type();
    return isTextField(type) || isTemporalField(type) ||
           type == TokenType::TRACK || type == TokenType::SIMILAR;
}

bool Parser::startsNot() const {
    const TokenType type = peek().type();
    return type == TokenType::NOT || type == TokenType::LEFT_PAREN ||
           isFilterStart() || isValue(type);
}

void Parser::fail(const std::string_view message) const {
    const Token& token = peek();
    const std::string found = token.type() == TokenType::END_OF_FILE
                                  ? "end of input"
                                  : "'" + token.lexeme() + "'";

    throw std::runtime_error(std::to_string(token.line()) + ": " +
                             std::string(message) + ", found " + found);
}

} // namespace Track8::Compiler
