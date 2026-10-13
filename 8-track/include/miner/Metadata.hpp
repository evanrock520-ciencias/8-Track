#pragma once
#include <filesystem>

namespace Track8::Miner {
struct Metadata {
    std::filesystem::path m_path;
    std::string m_title = "Unknown";
    std::string m_performer = "Unknown";
    std::string m_album = "Unknown";
    std::string m_genre = "Unknown";
    unsigned int m_year = 2026;
    unsigned int m_trackNumber = 1;
};
} // namespace Track8::Miner