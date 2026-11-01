#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationName("8-track");

    QQmlApplicationEngine engine;
    engine.loadFromModule("Track8", "Main");

    return app.exec();
}