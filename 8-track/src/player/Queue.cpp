#include <algorithm>
#include <stdexcept>

#include "player/Queue.hpp"

namespace Track8::Player {

Queue::Queue(const std::vector<Domain::Song>& songs)
    : m_queue(songs.begin(), songs.end()),
      m_original(songs.begin(), songs.end()) {
    next();
}

void Queue::addSong(const Domain::Song& song) {
    m_queue.push_back(song);
    m_original.push_back(song);
}

void Queue::userAddSong(const Domain::Song& song) {
    m_userQueue.push_back(song);
}

void Queue::next() {
    if (m_current) {
        m_history.push(std::move(*m_current));
        m_current.reset();
    }

    if (!m_userQueue.empty()) {
        m_current = std::move(m_userQueue.front());
        m_userQueue.pop_front();
        return;
    }

    if (m_queue.empty())
        return;

    if (const auto it = std::ranges::find(m_original, m_queue.front());
        it != m_original.end())
        m_original.erase(it);
    m_current = std::move(m_queue.front());
    m_queue.pop_front();
}

void Queue::playNext(const Domain::Song& song) {
    m_userQueue.push_front(song);
}

void Queue::previous() {
    if (m_history.empty())
        return;

    if (m_current)
        m_userQueue.push_front(std::move(*m_current));
    m_current = m_history.top();
    m_history.pop();
}

void Queue::remove(const Domain::Song& song) {
    if (const auto it = std::ranges::find(m_queue, song); it != m_queue.end())
        m_queue.erase(it);
    if (const auto it = std::ranges::find(m_original, song);
        it != m_original.end())
        m_original.erase(it);
}

void Queue::shuffle() {
    std::ranges::shuffle(m_queue, m_rng);
}

Domain::Song Queue::current() {
    if (!m_current)
        throw std::out_of_range("queue has no current song");
    return *m_current;
}

void Queue::disableShuffle() {
    m_queue = m_original;
}

std::size_t Queue::size() const {
    return m_queue.size() + m_userQueue.size() + (m_current ? 1 : 0);
}

std::vector<Domain::Song> Queue::songsInQueue() {
    std::vector<Domain::Song> songs;
    songs.reserve(1 + m_userQueue.size() + m_queue.size());

    if (m_current)
        songs.push_back(m_current.value());

    songs.insert(songs.end(), m_userQueue.begin(), m_userQueue.end());

    songs.insert(songs.end(), m_queue.begin(), m_queue.end());

    return songs;
}

std::vector<Domain::Song> Queue::songsInHistory() const {
    auto history = m_history;
    std::vector<Domain::Song> songs;

    songs.reserve(history.size());

    while (!history.empty()) {
        songs.push_back(history.top());
        history.pop();
    }

    return songs;
}

} // namespace Track8::Player