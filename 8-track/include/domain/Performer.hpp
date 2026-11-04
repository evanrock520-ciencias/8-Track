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
    Performer(const int id, std::string name,
              const PerformerType type = PerformerType::Unknown)
        : m_id(id), m_name(std::move(name)), m_type(type) {};
    virtual ~Performer() = default;

    [[nodiscard]] int id() const { return m_id; };
    [[nodiscard]] const std::string& name() const { return m_name; };
    [[nodiscard]] PerformerType type() const { return m_type; };

    bool operator==(const Performer& performer) const = default;

protected:
    int m_id = -1;
    std::string m_name;
    PerformerType m_type = PerformerType::Unknown;
};
} // namespace Track8::Domain