#include "gtest/gtest.h"

#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "domain/repositories/IAlbumRepository.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "domain/repositories/ISongRepository.hpp"
#include "services/SearchService.hpp"

#include <memory>

using namespace Track8;

class SearchServiceTest : public ::testing::Test {
protected:
    void SetUp() {
        m_manager = std::make_unique<Database::DatabaseManager>(":memory:");
        const auto database = m_manager->database();
        m_performers =
            std::make_shared<Database::SQLitePerformerRepository>(database);
        m_albums = std::make_shared<Database::SQLiteAlbumRepository>(database);
        m_songs = std::make_shared<Database::SQLiteSongRepository>(
            database, m_performers, m_albums);
        m_search = std::make_unique<Services::SearchService>(m_songs);
    };

    void TearDown() {
        m_search.reset();
        m_albums.reset();
        m_performers.reset();
        m_songs.reset();
        m_manager.reset();
    }

    std::unique_ptr<Services::SearchService> m_search;
    std::unique_ptr<Database::DatabaseManager> m_manager;
    std::shared_ptr<IAlbumRepository> m_albums;
    std::shared_ptr<IPerformerRepository> m_performers;
    std::shared_ptr<ISongRepository> m_songs;
};

TEST_F(SearchServiceTest, ValidQuery) {
    constexpr int SONGS = 100;

    const auto performer = m_performers->find(m_performers->save("Lamp"));
    const auto album = m_albums->find(0); // álbum "Unknown"

    for (int i = 1; i <= SONGS; ++i) {
        Domain::SongBuilder builder;
        m_songs->save(builder.with_title("Song" + std::to_string(i))
                          .with_year(1920 + i)
                          .with_album(album)
                          .with_performer(performer)
                          .create());
    }

    const auto result = m_search->search("year: 1990 =>");
    ASSERT_TRUE(result.success);
    ASSERT_EQ(result.songs.size(), 31);
}

TEST_F(SearchServiceTest, InvalidQuery) {
    constexpr int SONGS = 100;

    const auto performer = m_performers->find(m_performers->save("Lamp"));
    const auto album = m_albums->find(0); // álbum "Unknown"

    for (int i = 1; i <= SONGS; ++i) {
        Domain::SongBuilder builder;
        m_songs->save(builder.with_title("Song" + std::to_string(i))
                          .with_year(1920 + i)
                          .with_album(album)
                          .with_performer(performer)
                          .create());
    }

    const auto result = m_search->search(R"(label: "Jagjaguwar")");
    ASSERT_FALSE(result.success);
}

TEST_F(SearchServiceTest, EmptyResultQuery) {
    constexpr int SONGS = 100;

    const auto performer = m_performers->find(m_performers->save("Lamp"));
    const auto album = m_albums->find(0); // álbum "Unknown"

    for (int i = 1; i <= SONGS; ++i) {
        Domain::SongBuilder builder;
        m_songs->save(builder.with_title("Song" + std::to_string(i))
                          .with_year(1920 + i)
                          .with_album(album)
                          .with_performer(performer)
                          .create());
    }

    const auto result = m_search->search(R"(performer: "Kasabian")");
    ASSERT_TRUE(result.success);
    ASSERT_EQ(result.songs.size(), 0);
}

TEST_F(SearchServiceTest, EmptyQueryGivesAllSongs) {
    constexpr int SONGS = 100;

    const auto performer = m_performers->find(m_performers->save("Lamp"));
    const auto album = m_albums->find(0); // álbum "Unknown"

    for (int i = 1; i <= SONGS; ++i) {
        Domain::SongBuilder builder;
        m_songs->save(builder.with_title("Song" + std::to_string(i))
                          .with_year(1920 + i)
                          .with_album(album)
                          .with_performer(performer)
                          .create());
    }

    const auto result = m_search->search("");
    ASSERT_TRUE(result.success);
    ASSERT_EQ(result.songs.size(), 100);
}