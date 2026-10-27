#pragma once
#include <string>
#include <utility>

namespace Track8::Domain {

/**
 * @enum PerformerType
 * @brief Tipos de intérprete almacenados en la tabla `types`.
 */
enum class PerformerType : int {
    Person = 0,
    Group = 1,
    Unknown = 2,
};

/**
 * @class Performer
 * @brief Representa a un `intérprete`, se utiliza como fallback al leer las
 * etiquetas ID3V2.4.
 */
class Performer {
public:
    Performer(const int id, std::string name)
        : m_id(id), m_name(std::move(name)) {};
    virtual ~Performer() = default;

    [[nodiscard]] int id() const { return m_id; };
    [[nodiscard]] const std::string& name() const { return m_name; };

    bool operator==(const Performer& performer) const = default;

protected:
    int m_id = -1;
    std::string m_name;
};
} // namespace Track8::Domain