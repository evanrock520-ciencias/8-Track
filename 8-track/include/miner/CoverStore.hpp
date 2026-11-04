#pragma once
#include <filesystem>
#include <string>

namespace Track8::Miner {

class CoverStore {
public:
    explicit CoverStore(std::filesystem::path cacheDirectory);

    std::filesystem::path albumCoverPath(const std::filesystem::path& albumPath,
                                         const std::string& albumName) const;

    std::filesystem::path performerCoverPath(const std::string& name) const;

    [[nodiscard]] std::filesystem::path cacheDirectory() const {
        return m_cacheDirectory;
    }

private:
    std::filesystem::path pathFor(const std::string& key) const;
    std::filesystem::path m_cacheDirectory;
};

} // namespace Track8::Miner
