#pragma once
#include "domain/Stats.hpp"
#include "gui/models/SongListModel.hpp"
#include "services/ArtistService.hpp"
#include "services/LibraryService.hpp"

#include <qobject.h>

namespace Track8::Gui {

/**
 * @class LibraryController
 * @brief Maneja la interacción entre el servicio `Library` y la interfaz
 * gráfica.
 */
class LibraryController : public QObject {
    Q_OBJECT
    Q_PROPERTY(int albumCount READ albumCount NOTIFY statsChanged)
    Q_PROPERTY(int songCount READ songCount NOTIFY statsChanged)
    Q_PROPERTY(int performerCount READ performerCount NOTIFY statsChanged)
    Q_PROPERTY(int genreCount READ genreCount NOTIFY statsChanged)
    Q_PROPERTY(int bandCount READ bandCount NOTIFY statsChanged)
    Q_PROPERTY(int personCount READ personCount NOTIFY statsChanged)
    Q_PROPERTY(int unknownCount READ unknownCount NOTIFY statsChanged)
    Q_PROPERTY(SongListModel* songs READ songs CONSTANT)

public:
    explicit LibraryController(Services::LibraryService& library,
                               Services::ArtistService& artists,
                               QObject* parent = nullptr);

    [[nodiscard]] unsigned int songCount() const {
        return m_stats.m_songsCount;
    }
    [[nodiscard]] unsigned int albumCount() const {
        return m_stats.m_albumsCount;
    }
    [[nodiscard]] unsigned int performerCount() const {
        return m_stats.m_performersCount;
    }
    [[nodiscard]] unsigned int genreCount() const {
        return m_stats.m_genresCount;
    }
    [[nodiscard]] unsigned int bandCount() const {
        return m_stats.m_bandsCount;
    }
    [[nodiscard]] unsigned int personCount() const {
        return m_stats.m_peopleCount;
    }
    [[nodiscard]] unsigned int unknownCount() const {
        return m_stats.m_unknownCount;
    }

    [[nodiscard]] SongListModel* songs() { return &m_songsModel; }

    Q_INVOKABLE void loadSongs();
    Q_INVOKABLE void refresh();

signals:
    void statsChanged();

private:
    Domain::Stats m_stats{};
    SongListModel m_songsModel;
    Services::LibraryService& m_library;
    Services::ArtistService& m_artists;
};

} // namespace Track8::Gui