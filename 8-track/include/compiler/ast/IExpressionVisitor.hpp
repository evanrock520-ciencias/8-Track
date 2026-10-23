#pragma once

namespace Track8::Compiler {

class BinaryExpressionNode;
class NegationExpressionNode;
class TextFilterNode;
class TemporalFilterNode;
class TrackFilterNode;
class FreeFilterNode;

/**
 * @class IExpressionVisitor
 * @brief Interfaz del visitante para recorrer el AST de una consulta MuQL.
 *
 * Cada nodo concreto llama a la sobrecarga de `visit` que le corresponde desde
 * su método `accept`.
 */
class IExpressionVisitor {
public:
    virtual ~IExpressionVisitor() = default;

    virtual void visit(const BinaryExpressionNode& node) = 0;
    virtual void visit(const NegationExpressionNode& node) = 0;
    virtual void visit(const TextFilterNode& node) = 0;
    virtual void visit(const TemporalFilterNode& node) = 0;
    virtual void visit(const TrackFilterNode& node) = 0;
    virtual void visit(const FreeFilterNode& node) = 0;
};

} // namespace Track8::Compiler
