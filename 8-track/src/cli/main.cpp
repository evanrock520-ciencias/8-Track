#include "app/AppContext.hpp"
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

    App::AppContext context(databaseDir.toStdString());

    if (argc > 1) {
        const Cli::Cli cli(context.library, context.search, context.artists);
        cli.run(argc, argv);
    }

    return 0;
}