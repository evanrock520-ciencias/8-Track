#include "services/LibraryService.hpp"

#include <iostream>

namespace Track8::Services {

LibraryService::LibraryService(
    const std::shared_ptr<Repositories::IAlbumRepository>& albums,
    const std::shared_ptr<Repositories::IPerformerRepository>& performers,
    const std::shared_ptr<Repositories::ISongRepository>& songs)
    : m_albums(albums), m_songs(songs), m_performers(performers) {}

void LibraryService::scan(const std::filesystem::path& path) const {
    const Miner::Miner miner(path);
    // TODO: Utilizar una función inyectada para verificar el progreso.
    miner.mine([&](const Miner::Metadata& metadata) {
        std::cout << "Scanning " << metadata.m_title << "\n" << std::endl;
        importTrack(metadata);
    });
}

void LibraryService::importTrack(const Miner::Metadata& metadata) const {
    const auto performer = findOrCreatePerformer(metadata.m_performer);
    const auto album = findOrCreateAlbum(
        metadata.m_album, metadata.m_path.parent_path(), metadata.m_year);

    Domain::SongBuilder builder;
    const Domain::Song song = builder.with_album(album)
                                  .with_genre(metadata.m_genre)
                                  .with_path(metadata.m_path)
                                  .with_performer(performer)
                                  .with_title(metadata.m_title)
                                  .with_track(metadata.m_trackNumber)
                                  .with_year(metadata.m_year)
                                  .create();
    if (m_songs->find(metadata.m_path))
        return;

    m_songs->save(song);
}

std::shared_ptr<Domain::Performer>
LibraryService::findOrCreatePerformer(const std::string& name) const {
    if (const auto performer = m_performers->find(name))
        return performer;

    m_performers->save(name);
    return m_performers->find(name);
}

std::shared_ptr<Domain::Album>
LibraryService::findOrCreateAlbum(const std::string& name,
                                  const std::filesystem::path& dir,
                                  const int year) const {
    if (name.empty() || name == "Unknown")
        return m_albums->find(0);

    if (const auto album = m_albums->find(name, dir))
        return album;

    m_albums->save(Domain::Album(-1, dir, name, year));
    return m_albums->find(name, dir);
}

Domain::Stats LibraryService::stats() const {
    return Domain::Stats{
        .m_albumsCount = m_albums->count(),
        .m_songsCount = m_songs->count(),
        .m_performersCount = m_performers->count(),
        .m_genresCount = static_cast<unsigned int>(m_songs->genres().size()),
        .m_bandsCount = m_performers->countByType(Domain::PerformerType::Group),
        .m_peopleCount =
            m_performers->countByType(Domain::PerformerType::Person),
        .m_unknownCount =
            m_performers->countByType(Domain::PerformerType::Unknown),
    };
}

std::vector<std::shared_ptr<Domain::Song>> LibraryService::songs() const {
    return m_songs->getAll();
}

std::vector<std::shared_ptr<Domain::Album>> LibraryService::albums() const {
    return m_albums->getAll();
}

std::vector<std::string> LibraryService::genres() const {
    return m_songs->genres();
}

std::vector<std::shared_ptr<Domain::Song>>
LibraryService::songsByAlbum(const int albumId) const {
    return m_songs->getByAlbum(albumId);
}

std::vector<std::shared_ptr<Domain::Song>>
LibraryService::songsByPerformer(const int performerId) const {
    return m_songs->getByPerformer(performerId);
}

std::vector<std::shared_ptr<Domain::Album>>
LibraryService::albumsByPerformer(const int performerId) const {
    return m_albums->getByPerformer(performerId);
}

} // namespace Track8::Services
