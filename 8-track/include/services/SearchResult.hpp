#pragma once
#include <memory>
#include <vector>

namespace Track8::Domain {
class Song;
}
namespace Track8::Services {

struct SearchResult {
    bool success;
    std::vector<std::shared_ptr<Domain::Song>> songs;
    std::string errorMessage;
};

} // namespace Track8::Services