#pragma once
#include <utility>

#include "Date.hpp"
#include "Performer.hpp"

#include <optional>

namespace Track8::Domain {

/**
 * @class Artist
 * @brief Representa a artistas solistas.
 */
class Artist : public Performer {
public:
    Artist(const int id, const std::string& stage_name, std::string real_name,
           const Date& birth_date, const Date& death_date)
        : Performer(id, stage_name),
          m_stage_name(stage_name),
          m_real_name(std::move(real_name)),
          m_birth_date(birth_date),
          m_death_date(death_date) {};

    [[nodiscard]] const std::string& stage_name() const {
        return m_stage_name;
    };
    [[nodiscard]] const std::string& real_name() const { return m_real_name; };
    [[nodiscard]] Date birth_date() const { return m_birth_date; };
    [[nodiscard]] std::optional<Date> death_date() const {
        return m_death_date;
    };

private:
    std::string m_stage_name;
    std::string m_real_name;
    Date m_birth_date;
    std::optional<Date> m_death_date;
};
} // namespace Track8::Domain