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
    Q_PROPERTY(bool playing READ playing NOTIFY playbackStateChanged)
    Q_PROPERTY(qint64 duration READ duration NOTIFY durationChanged)
    Q_PROPERTY(qint64 position READ position NOTIFY currentPositionChanged)

    Q_INVOKABLE void load(const QUrl& path) const;
    Q_INVOKABLE void next();
    Q_INVOKABLE void previous();
    Q_INVOKABLE void playFor(const SongListModel* model, int idx);
    Q_INVOKABLE void togglePlayback() const;

    explicit PlaybackController(Services::LibraryService& library,
                                QObject* parent = nullptr);

    [[nodiscard]] QString title() const;
    [[nodiscard]] QString artist() const;
    [[nodiscard]] QString album() const;
    [[nodiscard]] QUrl cover() const;
    [[nodiscard]] qint64 duration();
    [[nodiscard]] qint64 position();
    [[nodiscard]] bool playing();

signals:
    void currentSongChanged();
    void playbackStateChanged();
    void durationChanged();
    void currentPositionChanged();

private:
    Player::Queue m_queue;
    std::unique_ptr<Player::IAudioBackend> m_backend;
    Services::LibraryService& m_library;
    bool m_playing = false;
    qint64 m_duration = 0;
    qint64 m_position = 0;
};

} // namespace Track8::Gui