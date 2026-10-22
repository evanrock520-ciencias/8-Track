#pragma once
#include "compiler/ast/Filters.hpp"

#include <memory>
#include <optional>
#include <string>

namespace Track8::Compiler {

class IExpressionVisitor;

class IExpressionNode {
public:
    virtual ~IExpressionNode() = default;
    virtual void accept(IExpressionVisitor& visitor) const = 0;
};

class BinaryExpressionNode : public IExpressionNode {
public:
    BinaryExpressionNode(const BinaryOperation type,
                         std::unique_ptr<IExpressionNode> left,
                         std::unique_ptr<IExpressionNode> right)
        : m_type(type), m_left(std::move(left)), m_right(std::move(right)) {};

    void accept(IExpressionVisitor& visitor) const override {
        visitor.visit(*this);
    };

    [[nodiscard]] BinaryOperation type() const { return m_type; }
    [[nodiscard]] const IExpressionNode& left() const { return *m_left; }
    [[nodiscard]] const IExpressionNode& right() const { return *m_right; }

private:
    BinaryOperation m_type;
    std::unique_ptr<IExpressionNode> m_left;
    std::unique_ptr<IExpressionNode> m_right;
};

class NegationExpressionNode : public IExpressionNode {
public:
    explicit NegationExpressionNode(std::unique_ptr<IExpressionNode> expression)
        : m_expression(std::move(expression)) {}

    void accept(IExpressionVisitor& visitor) const override {
        visitor.visit(*this);
    };

    [[nodiscard]] const IExpressionNode& expression() const {
        return *m_expression;
    }

private:
    std::unique_ptr<IExpressionNode> m_expression;
};

class TextFilterNode : public IExpressionNode {
public:
    TextFilterNode(const FilterField type, const std::string& value,
                   const MatchMode mode)
        : m_type(type), m_value(value), m_mode(mode) {}

    void accept(IExpressionVisitor& visitor) const override {
        visitor.visit(*this);
    };

    [[nodiscard]] FilterField type() const { return m_type; }
    [[nodiscard]] const std::string& value() const { return m_value; }
    [[nodiscard]] MatchMode mode() const { return m_mode; }

private:
    FilterField m_type;
    std::string m_value;
    MatchMode m_mode;
};

class TrackFilterNode : public IExpressionNode {
public:
    TrackFilterNode(const std::optional<int> from, const std::optional<int> to)
        : m_from(from), m_to(to) {}

    void accept(IExpressionVisitor& visitor) const override {
        visitor.visit(*this);
    };

    [[nodiscard]] std::optional<int> from() const { return m_from; }
    [[nodiscard]] std::optional<int> to() const { return m_to; }

private:
    std::optional<int> m_from;
    std::optional<int> m_to;
};

class TemporalFilterNode : public IExpressionNode {
public:
    TemporalFilterNode(const std::optional<int> from,
                       const std::optional<int> to)
        : m_from(from), m_to(to) {}

    void accept(IExpressionVisitor& visitor) const override {
        visitor.visit(*this);
    };

    [[nodiscard]] std::optional<int> from() const { return m_from; }
    [[nodiscard]] std::optional<int> to() const { return m_to; }

private:
    std::optional<int> m_from;
    std::optional<int> m_to;
};

class FreeFilterNode : public IExpressionNode {
public:
    explicit FreeFilterNode(const std::string& expression)
        : m_expression(expression) {}

    void accept(IExpressionVisitor& visitor) const override {
        visitor.visit(*this);
    };

    [[nodiscard]] const std::string& expression() const { return m_expression; }

private:
    std::string m_expression;
};

} // namespace Track8::Compiler