#pragma once
#include "Artist.hpp"
#include "Date.hpp"
#include "Performer.hpp"

#include <memory>
#include <optional>
#include <vector>

namespace Track8::Domain {

/**
 * @class Group
 * @brief Representación de una `banda`.
 */
class Group : public Performer {
public:
    Group(const int id, const std::string& name, const Date& start_date,
          const Date& end_date)
        : Performer(id, name),
          m_start_date(start_date),
          m_end_date(end_date) {};

    [[nodiscard]] Date start_date() const { return m_start_date; };
    [[nodiscard]] std::optional<Date> end_date() const { return m_end_date; };
    [[nodiscard]] const std::vector<std::shared_ptr<Artist>>& members() const {
        return m_members;
    };

    void add_member(std::shared_ptr<Artist> artist) {
        if (artist)
            m_members.push_back(std::move(artist));
    };

private:
    Date m_start_date;
    std::optional<Date> m_end_date;
    std::vector<std::shared_ptr<Artist>> m_members;
};
} // namespace Track8::Domain