#pragma once
#include "SongListModel.hpp"
#include "player/IAudioBackend.hpp"
#include "player/Queue.hpp"
#include "services/LibraryService.hpp"

#include <QObject>
#include <QUrl>

namespace Track8::Gui {

class PlaybackController : public QObject {
    Q_OBJECT
public:
    Q_PROPERTY(QString title READ title NOTIFY currentSongChanged)
    Q_PROPERTY(QString artist READ artist NOTIFY currentSongChanged)
    Q_PROPERTY(QString album READ album NOTIFY currentSongChanged)
    Q_PROPERTY(QUrl cover READ cover NOTIFY currentSongChanged)

    Q_INVOKABLE void load(const QUrl& path) const;
    Q_INVOKABLE void play() const;
    Q_INVOKABLE void playFor(const SongListModel* model, int idx);

    explicit PlaybackController(Services::LibraryService& library,
                                QObject* parent = nullptr);

    [[nodiscard]] QString title() const;
    [[nodiscard]] QString artist() const;
    [[nodiscard]] QString album() const;
    [[nodiscard]] QUrl cover() const;

signals:
    void currentSongChanged();

private:
    Player::Queue m_queue;
    std::unique_ptr<Player::IAudioBackend> m_backend;
    Services::LibraryService& m_library;
};

} // namespace Track8::Gui