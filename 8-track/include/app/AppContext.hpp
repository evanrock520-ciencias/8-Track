#pragma once
#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "services/ArtistService.hpp"
#include "services/LibraryService.hpp"
#include "services/SearchService.hpp"

#include <filesystem>
#include <memory>

namespace Track8::App {

struct AppContext {
    explicit AppContext(const std::filesystem::path& databasePath)
        : database(databasePath),
          albums(std::make_shared<Database::SQLiteAlbumRepository>(
              database.database())),
          performers(std::make_shared<Database::SQLitePerformerRepository>(
              database.database())),
          songs(std::make_shared<Database::SQLiteSongRepository>(
              database.database(), performers, albums)),
          library(albums, performers, songs),
          search(songs),
          artists(performers) {}

    Database::DatabaseManager database;
    std::shared_ptr<Database::SQLiteAlbumRepository> albums;
    std::shared_ptr<Database::SQLitePerformerRepository> performers;
    std::shared_ptr<Database::SQLiteSongRepository> songs;

    Services::LibraryService library;
    Services::SearchService search;
    Services::ArtistService artists;
};

} // namespace Track8::App