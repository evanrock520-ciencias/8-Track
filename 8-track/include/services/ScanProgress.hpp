#pragma once
#include <cstddef>
#include <string>

struct ScanProgress {
    std::size_t current;
    std::size_t total;
    std::string currentFile;
};