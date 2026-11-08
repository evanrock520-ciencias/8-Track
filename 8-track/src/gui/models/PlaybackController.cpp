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
    m_backend->onDurationChanged([this](std::int64_t duration) {
        m_duration = duration;
        emit durationChanged();
    });

    m_backend->onPositionChanged([this](std::int64_t position) {
        m_position = position;
        emit currentPositionChanged();
    });

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
    if (m_shuffleEnabled)
        m_queue.shuffle();
}

void PlaybackController::next() {
    m_queue.next();
    if (m_queue.current()) {
        m_backend->load(m_queue.current()->path());
        m_backend->play();
        emit currentSongChanged();
    }
}

void PlaybackController::previous() {
    m_queue.previous();
    if (m_queue.current()) {
        m_backend->load(m_queue.current()->path());
        m_backend->play();
        emit currentSongChanged();
    }
}

bool PlaybackController::playing() {
    m_backend->onStateChanged([this](const Player::PlaybackState state) {
        const bool playing = state == Player::PlaybackState::Playing;
        if (m_playing == playing)
            return;

        m_playing = playing;
        emit playbackStateChanged();
    });

    return m_playing;
}

void PlaybackController::togglePlayback() const {
    if (!m_queue.current())
        return;

    if (m_playing)
        m_backend->pause();
    else
        m_backend->play();
}

qint64 PlaybackController::duration() const {
    return m_duration;
}

qint64 PlaybackController::position() const {
    return m_position;
}

void PlaybackController::seek(const qint64 position) const {
    m_backend->seek(position);
}

void PlaybackController::setVolume(const qint16 volume) const {
    m_backend->setVolume(volume / 100.0);
}

void PlaybackController::toggleShuffle() {
    m_shuffleEnabled = !m_shuffleEnabled;

    if (m_shuffleEnabled)
        m_queue.shuffle();
    else
        m_queue.disableShuffle();

    emit shuffleEnabledChanged();
}

bool PlaybackController::shuffleEnabled() const {
    return m_shuffleEnabled;
}

void PlaybackController::playAlbum(const int idx) {
    const auto albumSongs = m_library.songsByAlbum(idx);

    std::vector<Domain::Song> songs;
    songs.reserve(albumSongs.size());

    for (const auto& song : albumSongs) {
        if (song)
            songs.push_back(*song);
    }

    m_queue = Player::Queue(songs);

    const auto song = m_queue.current();
    if (!song)
        return;

    if (m_shuffleEnabled)
        m_queue.shuffle();

    m_backend->load(song->path());
    emit currentSongChanged();
    m_backend->play();
}
} // namespace Track8::Gui
