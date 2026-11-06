#pragma once
#include "AlbumListModel.hpp"
#include "PerformerListModel.hpp"
#include "domain/Stats.hpp"
#include "gui/models/SongListModel.hpp"
#include "services/ArtistService.hpp"
#include "services/LibraryService.hpp"
#include "services/SearchService.hpp"

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
    Q_PROPERTY(SongListModel* searchResults READ searchResults CONSTANT)
    Q_PROPERTY(QString searchError READ searchError NOTIFY searchErrorChanged)
    Q_PROPERTY(AlbumListModel* albums READ albums CONSTANT);
    Q_PROPERTY(PerformerListModel* performers READ performers CONSTANT);
    Q_PROPERTY(PerformerListModel* artists READ artists CONSTANT);

public:
    explicit LibraryController(Services::LibraryService& library,
                               Services::SearchService& search,
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

    [[nodiscard]] QString searchError() const { return m_searchError; }

    [[nodiscard]] SongListModel* songs() { return &m_songsModel; }
    [[nodiscard]] SongListModel* searchResults() { return &m_searchModel; }
    [[nodiscard]] AlbumListModel* albums() { return &m_albumsModel; }
    [[nodiscard]] PerformerListModel* performers() {
        return &m_performersModel;
    }
    [[nodiscard]] PerformerListModel* artists() { return &m_artistsModel; }

    Q_INVOKABLE void search(const QString& query);
    Q_INVOKABLE void clearSearch();
    Q_INVOKABLE void loadSongs();
    Q_INVOKABLE void loadAlbums();
    Q_INVOKABLE void loadPerformers();
    Q_INVOKABLE void loadArtists();
    Q_INVOKABLE void refresh();
    Q_INVOKABLE QString albumCover(const QString& path,
                                   const QString& name) const;
    Q_INVOKABLE QString performerCover(const QString& name) const;
    Q_INVOKABLE QVariantMap performerDetails(int id) const;
    Q_INVOKABLE bool savePerformer(int id, const QString& name,
                                   int selectedType, const QString& realName,
                                   const QString& birthDate,
                                   const QString& deathDate,
                                   const QString& startDate,
                                   const QString& endDate);
    Q_INVOKABLE QList<int> members(int bandId) const;
    Q_INVOKABLE void updateMembers(int bandId,
                                   const QList<int>& selectedIds) const;

signals:
    void statsChanged();
    void searchErrorChanged();

private:
    Domain::Stats m_stats{};
    SongListModel m_songsModel;
    SongListModel m_searchModel;
    AlbumListModel m_albumsModel;
    PerformerListModel m_performersModel;
    PerformerListModel m_artistsModel;
    Services::LibraryService& m_library;
    Services::SearchService& m_search;
    Services::ArtistService& m_artists;

    QString m_searchError;
};

} // namespace Track8::Gui
