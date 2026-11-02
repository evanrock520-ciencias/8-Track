#pragma once
#include <filesystem>

namespace Track8::Miner {

struct Covers {
    std::filesystem::path album;
    std::filesystem::path artist;
};

} // namespace Track8::Miner