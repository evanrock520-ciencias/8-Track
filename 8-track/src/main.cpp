#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "miner/Miner.hpp"
#include "services/LibraryService.hpp"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QString>
#include <argparse/argparse.hpp>
#include <iostream>
#include <string>

using namespace Track8;

int main(int argc, char* argv[]) {
    QCoreApplication application(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("8-track"));
    argparse::ArgumentParser program("8-track");

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

    program.add_argument("--scan", "-s")
        .help("scan a directory for MP3 files.");
    program.add_argument("--query", "-q")
        .help("search the music metadata database.");

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
        std::cerr << program;
        return 1;
    }

    // Si se solicita escanear un directorio.
    if (program.is_used("--scan")) {
        const auto path = program.get<std::string>("--scan");
        std::cout << "Scanning " << path << '\n';
        // TODO: Minar un directorio.
        library.scan(path);
    }

    // Si se solicita realizar una consulta por consola.
    if (program.is_used("--query")) {
        const auto query = program.get<std::string>("--query");

        std::cout << "Querying " << query << '\n';
        // TODO: Tabular la consulta
    }

    // TODO: Lanzar la aplicación gráfica.

    return 0;
}