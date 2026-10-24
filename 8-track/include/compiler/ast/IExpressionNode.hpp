#pragma once
#include "IExpressionVisitor.hpp"

namespace Track8::Compiler {

/**
 * @interface IExpressionNode
 * @brief Interfaz representativa de los nodos de un árbol de sintáxis.
 */
class IExpressionNode {
public:
    virtual ~IExpressionNode() = default;
    virtual void accept(IExpressionVisitor& visitor) const = 0;

    bool operator==(const IExpressionNode& node) const = default;
};

} // namespace Track8::Compiler