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

} // namespace Track8::Player
