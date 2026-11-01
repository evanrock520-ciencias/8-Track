#include "app/AppContext.hpp"
#include "gui/models/LibraryController.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStandardPaths>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("8-track");

    const QString databaseDir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) +
        "/8-track.db";

    Track8::App::AppContext context(databaseDir.toStdString());
    Track8::Gui::LibraryController libraryController(context.library,
                                                     context.artists);

    qmlRegisterUncreatableType<Track8::Gui::SongListModel>(
        "Track8.Backend", 1, 0, "SongListModel", "");
    qmlRegisterSingletonInstance("Track8.Backend", 1, 0, "Library",
                                 &libraryController);

    QQmlApplicationEngine engine;
    engine.loadFromModule("Track8", "Main");

    return app.exec();
}