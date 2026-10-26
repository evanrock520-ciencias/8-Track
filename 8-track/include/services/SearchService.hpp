#pragma once
#include "SearchResult.hpp"
#include "domain/Song.hpp"
#include "domain/repositories/ISongRepository.hpp"

namespace Track8::Services {

class SearchService {
public:
    explicit SearchService(
        const std::shared_ptr<Repositories::ISongRepository>& songs)
        : m_songs(songs) {}
    [[nodiscard]] SearchResult search(const std::string& source) const;

private:
    std::shared_ptr<Repositories::ISongRepository> m_songs;
};

} // namespace Track8::Services