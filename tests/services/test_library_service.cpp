#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "domain/repositories/IAlbumRepository.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "domain/repositories/ISongRepository.hpp"
#include "miner/Metadata.hpp"
#include "services/LibraryService.hpp"

#include <gtest/gtest.h>

using namespace Track8;

class LibraryServiceTest : public ::testing::Test {
protected:
    void SetUp() {
        m_manager = std::make_unique<Database::DatabaseManager>(":memory:");
        const auto database = m_manager->database();
        m_performers =
            std::make_shared<Database::SQLitePerformerRepository>(database);
        m_albums = std::make_shared<Database::SQLiteAlbumRepository>(database);
        m_songs = std::make_shared<Database::SQLiteSongRepository>(
            database, m_performers, m_albums);
        m_library = std::make_unique<Services::LibraryService>(
            m_albums, m_performers, m_songs);
    };

    void TearDown() {
        m_library.reset();
        m_albums.reset();
        m_performers.reset();
        m_songs.reset();
        m_manager.reset();
    }

    std::unique_ptr<Services::LibraryService> m_library;
    std::unique_ptr<Database::DatabaseManager> m_manager;
    std::shared_ptr<IAlbumRepository> m_albums;
    std::shared_ptr<IPerformerRepository> m_performers;
    std::shared_ptr<ISongRepository> m_songs;
};

TEST_F(LibraryServiceTest, ImportTrack) {
    const Miner::Metadata metadata{.m_path =
                                       "/home/user/Music/funeral/wake-up.mp3",
                                   .m_title = "Wake Up",
                                   .m_performer = "Arcade Fire",
                                   .m_album = "Funeral",
                                   .m_genre = "Chamber Pop",
                                   .m_year = 2004,
                                   .m_trackNumber = 7};

    m_library->importTrack(metadata);
    const auto [m_albumsCount, m_songsCount, m_performersCount] =
        m_library->stats();
    ASSERT_EQ(m_songsCount, 1);
    ASSERT_EQ(m_performersCount, 1);
    ASSERT_EQ(m_albumsCount, 2); // Siempre existe al menos un álbum 'Unknown'
}

TEST_F(LibraryServiceTest, ImportTracksWithSamePerformer) {
    const Miner::Metadata metadataWakeUp{
        .m_path = "/home/user/Music/funeral/wake-up.mp3",
        .m_title = "Wake Up",
        .m_performer = "Arcade Fire",
        .m_album = "Funeral",
        .m_genre = "Chamber Pop",
        .m_year = 2004,
        .m_trackNumber = 7};

    const Miner::Metadata metadataTheSuburbs{
        .m_path = "/home/user/Music/the-suburbs/the-suburbs.mp3",
        .m_title = "The Suburbs",
        .m_performer = "Arcade Fire",
        .m_album = "The Suburbs",
        .m_genre = "Baroque Pop",
        .m_year = 2010,
        .m_trackNumber = 1};

    m_library->importTrack(metadataTheSuburbs);
    m_library->importTrack(metadataWakeUp);

    const auto [m_albumsCount, m_songsCount, m_performersCount] =
        m_library->stats();
    ASSERT_EQ(m_songsCount, 2);
    ASSERT_EQ(m_performersCount, 1); // Mismo intérprete
    ASSERT_EQ(m_albumsCount, 3); // Siempre existe al menos un álbum 'Unknown'
}

TEST_F(LibraryServiceTest, ImportTracksWithSamePerformerAndAlbum) {
    const Miner::Metadata metadataWakeUp{
        .m_path = "/home/user/Music/funeral/wake-up.mp3",
        .m_title = "Wake Up",
        .m_performer = "Arcade Fire",
        .m_album = "Funeral",
        .m_genre = "Chamber Pop",
        .m_year = 2004,
        .m_trackNumber = 7};

    const Miner::Metadata metadataHaiti{
        .m_path = "/home/user/Music/funeral/haiti.mp3",
        .m_title = "Haiti",
        .m_performer = "Arcade Fire",
        .m_album = "Funeral",
        .m_genre = "Chamber Pop",
        .m_year = 2004,
        .m_trackNumber = 8};

    m_library->importTrack(metadataHaiti);
    m_library->importTrack(metadataWakeUp);

    const auto [m_albumsCount, m_songsCount, m_performersCount] =
        m_library->stats();
    ASSERT_EQ(m_songsCount, 2);
    ASSERT_EQ(m_performersCount, 1); // Mismo intérprete
    ASSERT_EQ(m_albumsCount, 2);     // Mismo álbum
}

TEST_F(LibraryServiceTest, TrackWithUnknownAlbum) {
    const Miner::Metadata metadata{.m_path = "/home/user/Music/andromeda.mp3",
                                   .m_title = "Andromeda",
                                   .m_performer = "Weyes Blood",
                                   .m_album = "Unknown",
                                   .m_genre = "Baroque Pop",
                                   .m_year = 2019,
                                   .m_trackNumber = 2};

    m_library->importTrack(metadata);
    const auto [m_albumsCount, m_songsCount, m_performersCount] =
        m_library->stats();
    ASSERT_EQ(m_songsCount, 1);
    ASSERT_EQ(m_performersCount, 1);
    ASSERT_EQ(m_albumsCount, 1);

    const auto song = m_library->songs().at(0);
    ASSERT_EQ(song->album()->id(), 0);
}

TEST_F(LibraryServiceTest, ImportSameTrack) {
    const Miner::Metadata metadata{.m_path =
                                       "/home/user/Music/funeral/wake-up.mp3",
                                   .m_title = "Wake Up",
                                   .m_performer = "Arcade Fire",
                                   .m_album = "Funeral",
                                   .m_genre = "Chamber Pop",
                                   .m_year = 2004,
                                   .m_trackNumber = 7};

    m_library->importTrack(metadata);
    m_library->importTrack(metadata);
    const auto [m_albumsCount, m_songsCount, m_performersCount] =
        m_library->stats();
    ASSERT_EQ(m_songsCount, 1);
    ASSERT_EQ(m_performersCount, 1);
    ASSERT_EQ(m_albumsCount, 2); // Siempre existe al menos un álbum 'Unknown'
}