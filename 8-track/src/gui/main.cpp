#include "app/AppContext.hpp"
#include "gui/models/LibraryController.hpp"
#include "gui/models/PlaybackController.hpp"
#include "gui/models/ScanController.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("8-track");

    const QString databaseDir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/8-track.db";

    const auto coversDir =
        std::filesystem::path(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
                .toStdString()) /
        "covers";

    Track8::App::AppContext context(databaseDir.toStdString(), coversDir);
    Track8::Gui::LibraryController libraryController(
        context.library, context.search, context.artists);
    Track8::Gui::ScanController scanController(databaseDir.toStdString(),
                                               coversDir);
    Track8::Gui::PlaybackController playbackController(context.library);

    QObject::connect(&scanController, &Track8::Gui::ScanController::finished,
                     &libraryController,
                     [&libraryController](const bool success) {
                         if (!success)
                             return;

                         libraryController.refresh();
                         libraryController.loadSongs();
                         libraryController.loadAlbums();
                         libraryController.loadPerformers();
                     });

    qmlRegisterUncreatableType<Track8::Gui::SongListModel>(
        "Track8.Backend", 1, 0, "SongListModel", "");
    qmlRegisterSingletonInstance("Track8.Backend", 1, 0, "Library",
                                 &libraryController);
    qmlRegisterUncreatableType<Track8::Gui::AlbumListModel>(
        "Track8.Backend", 1, 0, "AlbumListModel", "");

    qmlRegisterSingletonInstance("Track8.Backend", 1, 0, "Scan",
                                 &scanController);

    qmlRegisterSingletonInstance("Track8.Backend", 1, 0, "Playback",
                                 &playbackController);

    QQmlApplicationEngine engine;
    engine.loadFromModule("Track8", "Main");

    return app.exec();
}