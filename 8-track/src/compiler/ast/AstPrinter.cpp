#include "compiler/ast/AstPrinter.hpp"
#include "compiler/ast/Nodes.hpp"

namespace Track8::Compiler {

std::string AstPrinter::print(const IExpressionNode& node) {
    m_result.clear();
    node.accept(*this);
    return m_result;
}

void AstPrinter::parenthesize(
    const std::string_view name,
    const std::initializer_list<const IExpressionNode*> nodes) {
    m_result += '(';
    m_result += name;
    for (const auto* node : nodes) {
        m_result += ' ';
        if (node) {
            node->accept(*this);
        }
    }
    m_result += ')';
}

void AstPrinter::visit(const BinaryExpressionNode& node) {
    parenthesize(toString(node.type()), {&node.left(), &node.right()});
}

void AstPrinter::visit(const NegationExpressionNode& node) {
    parenthesize("NOT", {&node.expression()});
}

void AstPrinter::visit(const TextFilterNode& node) {
    m_result += '(';
    switch (node.mode()) {
    case MatchMode::CONTAINS:
        m_result += toString(node.type());
        m_result += ": \"";
        m_result += node.value();
        m_result += '"';
        break;
    case MatchMode::EXACT:
        m_result += toString(node.type());
        m_result += ":= \"";
        m_result += node.value();
        m_result += '"';
        break;
    case MatchMode::SIMILAR:
        m_result += "similar: ";
        m_result += toString(node.type());
        m_result += " like \"";
        m_result += node.value();
        m_result += '"';
        break;
    }
    m_result += ')';
}

void AstPrinter::visit(const TemporalFilterNode& node) {
    m_result += "(year: ";
    if (node.from().has_value() && node.to().has_value()) {
        if (node.from().value() == node.to().value()) {
            m_result += std::to_string(node.from().value());
        } else {
            m_result += std::to_string(node.from().value());
            m_result += " => ";
            m_result += std::to_string(node.to().value());
        }
    } else if (node.from().has_value()) {
        m_result += std::to_string(node.from().value());
        m_result += " =>";
    } else if (node.to().has_value()) {
        m_result += "=> ";
        m_result += std::to_string(node.to().value());
    }
    m_result += ')';
}

void AstPrinter::visit(const TrackFilterNode& node) {
    m_result += "(track: ";
    if (node.from().has_value() && node.to().has_value()) {
        if (node.from().value() == node.to().value()) {
            m_result += std::to_string(node.from().value());
        } else {
            m_result += std::to_string(node.from().value());
            m_result += " => ";
            m_result += std::to_string(node.to().value());
        }
    } else if (node.from().has_value()) {
        m_result += std::to_string(node.from().value());
        m_result += " =>";
    } else if (node.to().has_value()) {
        m_result += "=> ";
        m_result += std::to_string(node.to().value());
    }
    m_result += ')';
}

void AstPrinter::visit(const FreeFilterNode& node) {
    m_result += '"';
    m_result += node.expression();
    m_result += '"';
}

} // namespace Track8::Compiler