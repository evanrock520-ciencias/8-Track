#pragma once
#include "Album.hpp"
#include "Performer.hpp"
#include <filesystem>
#include <memory>
#include <stdexcept>
#include <string>

namespace Track8::Domain {

/**
 * @class Song
 * @brief Representación de una `rola`.
 */
class Song {
public:
    [[nodiscard]] int id() const { return m_id; }
    [[nodiscard]] const std::string& title() const { return m_title; }
    [[nodiscard]] const std::string& genre() const { return m_genre; }
    [[nodiscard]] const std::filesystem::path& path() const { return m_path; }
    [[nodiscard]] int year() const { return m_year; }
    [[nodiscard]] int track() const { return m_track_number; }
    [[nodiscard]] const std::shared_ptr<Album>& album() const {
        return m_album;
    }
    [[nodiscard]] const std::shared_ptr<Performer>& performer() const {
        return m_performer;
    }

    friend class SongBuilder;

private:
    Song() = default;

    int m_id = -1;
    std::filesystem::path m_path;
    std::string m_title;
    int m_track_number = 1;
    int m_year = 2026;
    std::string m_genre;
    std::shared_ptr<Album> m_album;
    std::shared_ptr<Performer> m_performer;
};

/**
 * @class SongBuilder
 * @brief Permite construir `rolas` encadenando setters.
 */
class SongBuilder {
public:
    SongBuilder() = default;

    [[nodiscard]] Song create() const { return std::move(m_song); }

    SongBuilder& with_id(const int id) {
        if (id < 0)
            throw std::invalid_argument("ID cannot be negative.");

        m_song.m_id = id;
        return *this;
    }

    SongBuilder& with_title(const std::string& title) {
        m_song.m_title = title;
        return *this;
    }

    SongBuilder& with_genre(const std::string& genre) {
        m_song.m_genre = genre;
        return *this;
    }

    SongBuilder& with_path(const std::filesystem::path& path) {
        m_song.m_path = path;
        return *this;
    }

    SongBuilder& with_year(const int year) {
        m_song.m_year = year;
        return *this;
    }

    SongBuilder& with_track(const int track_number) {
        m_song.m_track_number = track_number;
        return *this;
    }

    SongBuilder& with_album(const std::shared_ptr<Album>& album) {
        if (!album)
            throw std::invalid_argument("Album cannot be null.");

        m_song.m_album = album;
        return *this;
    }

    SongBuilder& with_performer(const std::shared_ptr<Performer>& performer) {
        if (!performer)
            throw std::invalid_argument("Performer cannot be null.");

        m_song.m_performer = performer;
        return *this;
    }

private:
    Song m_song;
};
} // namespace Track8::Domain