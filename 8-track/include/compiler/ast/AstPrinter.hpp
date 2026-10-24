#pragma once
#include "IExpressionVisitor.hpp"
#include "Nodes.hpp"

#include <initializer_list>
#include <string>
#include <string_view>
#include <vector>

namespace Track8::Compiler {

/**
 * @class AstPrinter
 * @brief Implementación de @ref IExpressionVisitor para recorrer árboles AST e
 * imprimirlos.
 */
class AstPrinter : public IExpressionVisitor {
public:
    std::string print(const IExpressionNode& node);

    void visit(const BinaryExpressionNode& node) override;
    void visit(const NegationExpressionNode& node) override;
    void visit(const TextFilterNode& node) override;
    void visit(const TemporalFilterNode& node) override;
    void visit(const TrackFilterNode& node) override;
    void visit(const FreeFilterNode& node) override;

private:
    /**
     * Imprime un nodo compuesto y lo parentiza.
     * @param name El nombre de la operación.
     * @param nodes Los nodos a parentizar.
     */
    void parenthesize(std::string_view name,
                      std::initializer_list<const IExpressionNode*> nodes);

    static constexpr std::string_view
    toString(const BinaryOperation operation) {
        switch (operation) {
        case BinaryOperation::AND:
            return "AND";
        case BinaryOperation::OR:
            return "OR";
        }
        return "UNKNOWN";
    }

    static constexpr std::string_view toString(const FilterField field) {
        switch (field) {
        case FilterField::PERFORMER:
            return "performer";
        case FilterField::ARTIST:
            return "artist";
        case FilterField::BAND:
            return "band";
        case FilterField::ALBUM:
            return "album";
        case FilterField::SONG:
            return "song";
        case FilterField::GENRE:
            return "genre";
        case FilterField::MEMBER:
            return "member";
        case FilterField::PATH:
            return "path";
        }
        return "unknown";
    }

    std::string m_result;
};

} // namespace Track8::Compiler