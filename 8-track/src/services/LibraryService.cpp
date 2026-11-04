#include "services/LibraryService.hpp"

#include "database/TransactionScope.hpp"
#include "miner/CoverMiner.hpp"
#include "services/ScanProgress.hpp"

#include <iostream>
#include <thread>

namespace Track8::Services {

LibraryService::LibraryService(
    const std::shared_ptr<Repositories::IAlbumRepository>& albums,
    const std::shared_ptr<Repositories::IPerformerRepository>& performers,
    const std::shared_ptr<Repositories::ISongRepository>& songs,
    const std::filesystem::path& cacheDir,
    std::shared_ptr<Repositories::ITransactionManager> transactions)
    : m_albums(albums),
      m_songs(songs),
      m_performers(performers),
      m_transactions(std::move(transactions)),
      m_coverStore(cacheDir) {}

void LibraryService::scan(
    const std::filesystem::path& path,
    const std::function<void(const ScanProgress&)>& onProgress) const {
    const Miner::Miner miner(path);
    Miner::CoverMiner coverMiner(m_coverStore.cacheDirectory());

    const std::size_t total = miner.count();
    std::size_t current = 0;
    std::vector<Miner::Metadata> tracks;

    auto report = [&](const std::size_t currentIndex,
                      const std::string& currentFile) {
        if (onProgress)
            onProgress({.current = currentIndex,
                        .total = total,
                        .currentFile = currentFile});
    };

    std::jthread worker([&] {
        miner.mine([&](const Miner::Metadata& data) {
            tracks.push_back(data);
            std::ignore = coverMiner.coverExtract(data.m_path, data.m_performer,
                                                  data.m_album);
            report(++current, data.m_title);
        });
    });
    worker.join();

    std::unique_ptr<Database::TransactionScope> scope;
    if (m_transactions)
        scope = std::make_unique<Database::TransactionScope>(*m_transactions);

    for (const auto& track : tracks)
        importTrack(track);

    if (scope)
        scope->commit();

    report(total, {});
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

std::filesystem::path
LibraryService::albumCover(const std::filesystem::path& path,
                           const std::string& name) const {
    return m_coverStore.albumCoverPath(path, name);
}

std::filesystem::path
LibraryService::performerCover(const std::string& name) const {
    return m_coverStore.performerCoverPath(name);
}

} // namespace Track8::Services
