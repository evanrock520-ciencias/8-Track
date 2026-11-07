#include "gui/models/PlaybackController.hpp"

#include "player/QtMultimediaBackend.hpp"

#include <QUrl>
#include <utility>

namespace Track8::Gui {

PlaybackController::PlaybackController(Services::LibraryService& library,
                                       QObject* parent)
    : QObject(parent),
      m_queue({}),
      m_backend(std::make_unique<Player::QtMultimediaBackend>()),
      m_library(library) {
    m_backend->onFinished([this] {
        m_queue.next();

        if (const auto song = m_queue.current()) {
            m_backend->load(song->path());
            m_backend->play();
        } else
            m_backend->stop();

        emit currentSongChanged();
    });
}

QString PlaybackController::title() const {
    const auto song = m_queue.current();
    return song ? QString::fromStdString(song->title()) : QString{};
}

QString PlaybackController::artist() const {
    const auto song = m_queue.current();
    return song && song->performer()
               ? QString::fromStdString(song->performer()->name())
               : QString{};
}

QString PlaybackController::album() const {
    const auto song = m_queue.current();
    return song && song->album() ? QString::fromStdString(song->album()->name())
                                 : QString{};
}

QUrl PlaybackController::cover() const {
    const auto song = m_queue.current();
    if (!song || !song->album())
        return {};

    const auto path =
        m_library.albumCover(song->album()->path(), song->album()->name());
    if (!std::filesystem::exists(path))
        return {};
    return QUrl::fromLocalFile(QString::fromStdString(path.string()));
}

void PlaybackController::load(const QUrl& path) const {
    m_backend->load(path.toLocalFile().toStdString());
}

void PlaybackController::play() const {
    m_backend->play();
}

void PlaybackController::playFor(const SongListModel* model, const int idx) {
    if (!model || idx < 0 || idx >= model->count())
        return;

    std::vector<Domain::Song> songs;
    songs.reserve(model->count());

    for (int i = 0; i < model->count(); ++i)
        songs.push_back(*model->songAt(i));
    const Player::Queue queue(songs);

    m_queue = queue;
    for (int i = 0; i < idx; i++)
        m_queue.next();

    const auto song = m_queue.current();
    if (!song)
        return;

    m_backend->load(song->path());
    emit currentSongChanged();
    m_backend->play();
}

} // namespace Track8::Gui