#include "gui/models/PlaybackController.hpp"

#include "player/QtMultimediaBackend.hpp"

#include <QUrl>

namespace Track8::Gui {

PlaybackController::PlaybackController(QObject* parent)
    : QObject(parent),
      m_queue({}),
      m_backend(std::make_unique<Player::QtMultimediaBackend>()) {}

void PlaybackController::load(const QUrl& path) const {
    m_backend->load(path.toLocalFile().toStdString());
}

void PlaybackController::play() const {
    m_backend->play();
}

} // namespace Track8::Gui