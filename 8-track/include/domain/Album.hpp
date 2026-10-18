#pragma once
#include <filesystem>
#include <utility>

namespace Track8::Domain {

/**
 * @class Album
 * @brief Representación de un `albúm`
 */
class Album {
public:
    Album(const int id, std::filesystem::path path, std::string name,
          const int year)
        : m_id(id),
          m_path(std::move(path)),
          m_name(std::move(name)),
          m_year(year) {};

    [[nodiscard]] int id() const { return m_id; };
    [[nodiscard]] int year() const { return m_year; };
    [[nodiscard]] const std::string& name() const { return m_name; };
    [[nodiscard]] const std::filesystem::path& path() const { return m_path; };

    bool operator==(const Album& other) const = default;

private:
    int m_id = -1;
    std::filesystem::path m_path;
    std::string m_name;
    int m_year = 2026;
};
} // namespace Track8::Domain