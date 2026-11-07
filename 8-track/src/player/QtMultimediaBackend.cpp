#include "player/QtMultimediaBackend.hpp"
#include <QUrl>
#include <utility>

namespace Track8::Player {

QtMultimediaBackend::QtMultimediaBackend() {
    m_player.setAudioOutput(&m_output);
    QObject::connect(&m_player, &QMediaPlayer::mediaStatusChanged, &m_player,
                     [this](const QMediaPlayer::MediaStatus status) {
                         if (status == QMediaPlayer::EndOfMedia &&
                             m_finishedCallback)
                             m_finishedCallback();
                     });
    QObject::connect(&m_player, &QMediaPlayer::playbackStateChanged, &m_player,
                     [this](const QMediaPlayer::PlaybackState state) {
                         if (!m_stateChangedCallback)
                             return;

                         switch (state) {
                         case QMediaPlayer::PlayingState:
                             m_stateChangedCallback(PlaybackState::Playing);
                             break;
                         case QMediaPlayer::PausedState:
                             m_stateChangedCallback(PlaybackState::Paused);
                             break;
                         case QMediaPlayer::StoppedState:
                             m_stateChangedCallback(PlaybackState::Stopped);
                             break;
                         }
                     });
    QObject::connect(&m_player, &QMediaPlayer::durationChanged, &m_player,
                     [this](const qint64 duration) {
                         if (m_durationChangedCallback)
                             m_durationChangedCallback(
                                 static_cast<std::int64_t>(duration));
                     });
    QObject::connect(&m_player, &QMediaPlayer::positionChanged, &m_player,
                     [this](const qint64 position) {
                         if (m_positionChangedCallback)
                             m_positionChangedCallback(position);
                     });
}

void QtMultimediaBackend::load(const std::filesystem::path& path) {
    m_player.setSource(
        QUrl::fromLocalFile(QString::fromStdString(path.string())));
}

void QtMultimediaBackend::play() {
    m_player.play();
}

void QtMultimediaBackend::pause() {
    m_player.pause();
}

void QtMultimediaBackend::stop() {
    m_player.stop();
}

void QtMultimediaBackend::seek(const int64_t positionMs) {
    m_player.setPosition(positionMs);
}

void QtMultimediaBackend::setVolume(const float volume) {
    m_output.setVolume(volume);
}

void QtMultimediaBackend::onFinished(std::function<void()> callback) {
    m_finishedCallback = std::move(callback);
}

void QtMultimediaBackend::onStateChanged(
    std::function<void(PlaybackState)> callback) {
    m_stateChangedCallback = std::move(callback);
}

void QtMultimediaBackend::onDurationChanged(
    std::function<void(std::int64_t)> callback) {
    m_durationChangedCallback = std::move(callback);
}

void QtMultimediaBackend::onPositionChanged(
    std::function<void(std::int64_t)> callback) {
    m_positionChangedCallback = std::move(callback);
}

} // namespace Track8::Player
