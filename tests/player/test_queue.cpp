#include "player/Queue.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using Track8::Player::Queue;
using namespace Track8::Domain;

class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        fillSongs();
        queue = std::make_unique<Queue>(m_songs);
    }

    static bool byId(const Song& song, const Song& other) {
        return song.id() < other.id();
    }

    void fillSongs() {
        const auto artist = std::make_shared<Performer>(1, "Angel Olsen");

        const auto album = std::make_shared<Album>(
            1, "/home/user/Music/big-time", "Big Time", 2022);

        const std::vector<std::string> songNames = {
            "All The Good Times",   "Big Time",
            "Dream Thing",          "Ghost On",
            "All The Flowers",      "Right Now",
            "This Is How It Works", "Go Home",
            "Through The Fires",    "Chasing The Sun"};

        int idx = 1;

        for (const auto& name : songNames) {
            SongBuilder builder;

            auto song = builder.with_album(album)
                            .with_performer(artist)
                            .with_id(idx++)
                            .with_title(name)
                            .with_path(album->path() / name)
                            .create();

            m_songs.push_back(std::move(song));
        }
    }

    std::vector<Song> m_songs;
    std::unique_ptr<Queue> queue;
};

TEST_F(QueueTest, FollowsInsertionOrder) {
    ASSERT_EQ(queue->size(), m_songs.size());

    for (const auto& expected : m_songs) {
        EXPECT_EQ(queue->current().id(), expected.id());
        queue->next();
    }
}

TEST_F(QueueTest, NextAdvancesSong) {
    queue->next();

    EXPECT_EQ(queue->current().id(), m_songs[1].id());
}

TEST_F(QueueTest, PlayNext) {
    SongBuilder builder;
    const Song song = builder.with_id(11).with_title("Dagger").create();
    queue->playNext(song);

    EXPECT_EQ(queue->current().id(), m_songs.front().id());
    queue->next();
    EXPECT_EQ(queue->current().id(), song.id());
}

TEST_F(QueueTest, UserAddSongToQueue) {
    SongBuilder builder;
    const Song song = builder.with_id(11).with_title("Dagger").create();
    queue->userAddSong(song);

    EXPECT_EQ(queue->current().id(), m_songs.front().id());
    queue->next();

    EXPECT_EQ(queue->current().id(), song.id());
    queue->next();
    EXPECT_EQ(queue->current().id(), m_songs[1].id());
}

TEST_F(QueueTest, EnableShuffle) {
    const auto currentId = queue->current().id();
    queue->shuffle();

    EXPECT_EQ(queue->current().id(), currentId);
    EXPECT_EQ(queue->size(), m_songs.size());

    auto shuffled = queue->songsInQueue();
    auto original = m_songs;

    std::ranges::sort(shuffled, byId);
    std::ranges::sort(original, byId);

    EXPECT_EQ(shuffled, original);
}

TEST_F(QueueTest, DisableShuffle) {
    queue->shuffle();
    queue->disableShuffle();

    for (const auto& song : m_songs) {
        EXPECT_EQ(queue->current().id(), song.id());
        queue->next();
    }
}

TEST_F(QueueTest, PreviousSong) {
    const auto song = queue->current();
    queue->next();
    queue->previous();
    EXPECT_EQ(queue->current().id(), song.id());
}

TEST_F(QueueTest, RemoveSong) {
    const auto& song = m_songs[3];
    queue->remove(song);

    const auto songs = queue->songsInQueue();

    EXPECT_EQ(queue->size(), m_songs.size() - 1);
    EXPECT_EQ(std::ranges::find(songs, song), songs.end());
}

TEST_F(QueueTest, NextOnEmptyQueue) {
    for (std::size_t i = 0; i < m_songs.size(); ++i)
        queue->next();

    EXPECT_NO_THROW(queue->next());
}