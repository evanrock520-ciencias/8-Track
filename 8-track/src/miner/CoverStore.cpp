#include "miner/CoverStore.hpp"

#include "picosha2.h"

#include <utility>

namespace Track8::Miner {

CoverStore::CoverStore(std::filesystem::path cacheDirectory)
    : m_cacheDirectory(std::move(cacheDirectory)) {}

std::filesystem::path CoverStore::pathFor(const std::string& key) const {
    return m_cacheDirectory / (picosha2::hash256_hex_string(key) + ".jpg");
}

std::filesystem::path
CoverStore::albumCoverPath(const std::filesystem::path& albumPath,
                           const std::string& albumName) const {
    return pathFor(albumPath.string() + "|" + albumName);
}

std::filesystem::path
CoverStore::performerCoverPath(const std::string& name) const {
    return pathFor(name);
}

} // namespace Track8::Miner
