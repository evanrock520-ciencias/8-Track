#include "gui/models/LibraryController.hpp"

#include <QUrl>

namespace Track8::Gui {

LibraryController::LibraryController(Services::LibraryService& library,
                                     Services::SearchService& search,
                                     Services::ArtistService& artists,
                                     QObject* parent)
    : QObject(parent),
      m_stats(library.stats()),
      m_library(library),
      m_search(search),
      m_artists(artists) {}

void LibraryController::loadSongs() {
    m_songsModel.setSongs(m_library.songs());
}

void LibraryController::loadAlbums() {
    auto albums = m_library.albums();
    std::erase_if(albums, [](const std::shared_ptr<Domain::Album>& album) {
        return album->id() == 0;
    });

    m_albumsModel.setAlbums(std::move(albums));
}

void LibraryController::loadPerformers() {
    m_performersModel.setPerformers(m_artists.performers());
}

void LibraryController::refresh() {
    m_stats = m_library.stats();
    emit statsChanged();
}

void LibraryController::search(const QString& query) {
    const auto result = m_search.search(query.toStdString());

    if (result.success) {
        m_searchModel.setSongs(result.songs);
        m_searchError.clear();
    } else {
        m_searchModel.clear();
        m_searchError = QString::fromStdString(result.errorMessage);
    }

    emit searchErrorChanged();
}

void LibraryController::clearSearch() {
    m_searchModel.clear();
    m_searchError.clear();
    emit searchErrorChanged();
}

QString LibraryController::albumCover(const QString& path,
                                      const QString& name) const {
    const auto cover =
        m_library.albumCover(path.toStdString(), name.toStdString());

    if (!std::filesystem::exists(cover))
        return {};

    return QUrl::fromLocalFile(QString::fromStdString(cover.string()))
        .toString();
}

QString LibraryController::performerCover(const QString& path,
                                          const QString& name) const {
    return {};
}

} // namespace Track8::Gui