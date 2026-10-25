#pragma once
#include "compiler/ast/IExpressionNode.hpp"
#include "compiler/ast/Query.hpp"
#include "compiler/lexer/Token.hpp"
#include "domain/Range.hpp"

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Track8::Compiler {

/**
 * @class Parser
 * @brief Convierte tokens provenientes del @ref Lexer en árboles de sinxtáxis
 * abstracta.
 */
class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    /**
     * Regresa la query relacionada a la lista de tokens.
     * @return La query relacionada a la lista de tokens.
     */
    [[nodiscard]] Query parse();

private:
    std::unique_ptr<IExpressionNode> expression();
    std::unique_ptr<IExpressionNode> orExpression();
    std::unique_ptr<IExpressionNode> andExpression();
    std::unique_ptr<IExpressionNode> notExpression();
    std::unique_ptr<IExpressionNode> primary();
    std::unique_ptr<IExpressionNode> filter();
    std::unique_ptr<IExpressionNode> term();
    std::unique_ptr<IExpressionNode> textFilter();
    std::unique_ptr<IExpressionNode> temporalFilter();
    std::unique_ptr<IExpressionNode> trackFilter();
    std::unique_ptr<IExpressionNode> similarFilter();
    static std::unique_ptr<IExpressionNode>
    orAll(std::vector<std::unique_ptr<IExpressionNode>> nodes);
    int integer();
    std::vector<Domain::Range> rangeList();
    Domain::Range rangeItem();

    [[nodiscard]] const Token& peek(std::size_t offset = 0) const;
    [[nodiscard]] const Token& previous() const;
    [[nodiscard]] bool check(TokenType type) const;
    [[nodiscard]] bool isAtEnd() const;

    bool match(std::initializer_list<TokenType> types);
    bool match(TokenType type);
    const Token& advance();
    const Token& consume(TokenType type, std::string_view message);
    bool isFilterStart() const;
    bool startsNot() const;

    [[nodiscard]] std::string value();
    [[nodiscard]] std::vector<std::string> values();

    [[noreturn]] void fail(std::string_view message) const;

    std::size_t m_current = 0;
    std::vector<Token> m_tokens;
};

} // namespace Track8::Compiler
