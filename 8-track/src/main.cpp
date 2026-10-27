#include "cli/Cli.hpp"
#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "miner/Miner.hpp"
#include "services/LibraryService.hpp"
#include "services/SearchService.hpp"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QString>
#include <iostream>
#include <string>

using namespace Track8;

int main(int argc, char* argv[]) {
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("8-track"));

    const QString databaseDir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/8-track.db";
    const Database::DatabaseManager manager(databaseDir.toStdString());

    auto albums =
        std::make_shared<Database::SQLiteAlbumRepository>(manager.database());
    auto performers = std::make_shared<Database::SQLitePerformerRepository>(
        manager.database());
    const auto songs = std::make_shared<Database::SQLiteSongRepository>(
        manager.database(), performers, albums);

    Services::LibraryService library(albums, performers, songs);
    Services::SearchService search(songs);
    Services::ArtistService artists(performers);

    if (argc > 1) {
        const Cli::Cli cli(library, search, artists);
        cli.run(argc, argv);
    }

    return 0;
}