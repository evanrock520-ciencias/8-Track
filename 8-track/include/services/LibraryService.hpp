#pragma once

#include "domain/Stats.hpp"
#include "domain/repositories/IAlbumRepository.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "domain/repositories/ISongRepository.hpp"
#include "miner/Miner.hpp"
#include "services/LibraryService.hpp"

#include <qobject.h>

namespace Track8::Services {

class LibraryService {
public:
    LibraryService(
        const std::shared_ptr<Repositories::IAlbumRepository>& albums,
        const std::shared_ptr<Repositories::IPerformerRepository>& performers,
        const std::shared_ptr<Repositories::ISongRepository>& songs);
    ~LibraryService() = default;

    void scan(const std::filesystem::path& path) const;
    void importTrack(const Track8::Miner::Metadata& metadata) const;

    [[nodiscard]] std::vector<std::shared_ptr<Domain::Song>> songs() const;
    [[nodiscard]] Domain::Stats stats() const;

private:
    [[nodiscard]] std::shared_ptr<Domain::Performer>
    findOrCreatePerformer(const std::string& name) const;
    [[nodiscard]] std::shared_ptr<Domain::Album>
    findOrCreateAlbum(const std::string& name, const std::filesystem::path& dir,
                      int year) const;

    std::shared_ptr<Repositories::IAlbumRepository> m_albums;
    std::shared_ptr<Repositories::ISongRepository> m_songs;
    std::shared_ptr<Repositories::IPerformerRepository> m_performers;
};

} // namespace Track8::Services
