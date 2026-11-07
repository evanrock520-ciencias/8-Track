#pragma once
#include "player/IAudioBackend.hpp"
#include "player/Queue.hpp"

#include <QObject>

namespace Track8::Gui {

class PlaybackController : public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE void load(const QUrl& path) const;
    Q_INVOKABLE void play() const;

    explicit PlaybackController(QObject* parent = nullptr);

private:
    Player::Queue m_queue;
    std::unique_ptr<Player::IAudioBackend> m_backend;
};

} // namespace Track8::Gui