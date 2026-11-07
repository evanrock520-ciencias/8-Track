#include "player/Queue.hpp"
namespace Track8::Player {

Queue::Queue(const std::vector<Domain::Song>& songs)
    : m_queue(songs.begin(), songs.end()), m_history() {}

} // namespace Track8::Player