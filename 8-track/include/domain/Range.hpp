#pragma once
#include <optional>

namespace Track8::Domain {

struct Range {
    Range(const std::optional<int> from, const std::optional<int> to)
        : from(from), to(to) {}

    std::optional<int> from;
    std::optional<int> to;
};

} // namespace Track8::Domain