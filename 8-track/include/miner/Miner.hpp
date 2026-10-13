#pragma once
#include "Metadata.hpp"

#include <filesystem>

namespace Track8::Miner {
class Miner {
public:
    explicit Miner(const std::filesystem::path& path);
    ~Miner() = default;

    void mine(std::invocable<const Metadata&> auto callback);

private:
    Metadata parseFile(const std::filesystem::path& path);

    std::filesystem::path m_path;
};
} // namespace Track8::Miner