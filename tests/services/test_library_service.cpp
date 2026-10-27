#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include "domain/repositories/IAlbumRepository.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "domain/repositories/ISongRepository.hpp"
#include "miner/Metadata.hpp"
#include "services/LibraryService.hpp"

#include <algorithm>

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
    const auto stats = m_library->stats();
    ASSERT_EQ(stats.m_songsCount, 1);
    ASSERT_EQ(stats.m_performersCount, 1);
    ASSERT_EQ(stats.m_albumsCount,
              2); // Siempre existe al menos un álbum 'Unknown'
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

    const auto stats = m_library->stats();
    ASSERT_EQ(stats.m_songsCount, 2);
    ASSERT_EQ(stats.m_performersCount, 1); // Mismo intérprete
    ASSERT_EQ(stats.m_albumsCount,
              3); // Siempre existe al menos un álbum 'Unknown'
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

    const auto stats = m_library->stats();
    ASSERT_EQ(stats.m_songsCount, 2);
    ASSERT_EQ(stats.m_performersCount, 1); // Mismo intérprete
    ASSERT_EQ(stats.m_albumsCount, 2);     // Mismo álbum
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
    const auto stats = m_library->stats();
    ASSERT_EQ(stats.m_songsCount, 1);
    ASSERT_EQ(stats.m_performersCount, 1);
    ASSERT_EQ(stats.m_albumsCount, 1);

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
    const auto stats = m_library->stats();
    ASSERT_EQ(stats.m_songsCount, 1);
    ASSERT_EQ(stats.m_performersCount, 1);
    ASSERT_EQ(stats.m_albumsCount,
              2); // Siempre existe al menos un álbum 'Unknown'
}

TEST_F(LibraryServiceTest, AlbumsAndGenres) {
    m_library->importTrack({.m_path = "/home/user/Music/all-mirrors/lark.mp3",
                            .m_title = "Lark",
                            .m_performer = "Angel Olsen",
                            .m_album = "All Mirrors",
                            .m_genre = "Art Pop",
                            .m_year = 2019,
                            .m_trackNumber = 1});
    m_library->importTrack(
        {.m_path = "/home/user/Music/big-time/all-the-good-times.mp3",
         .m_title = "All the Good Times",
         .m_performer = "Angel Olsen",
         .m_album = "Big Time",
         .m_genre = "Americana",
         .m_year = 2022,
         .m_trackNumber = 1});

    const auto albums = m_library->albums();
    EXPECT_EQ(albums.size(), 3); // Incluye el álbum 'Unknown'
    EXPECT_NE(std::find_if(albums.begin(), albums.end(),
                           [](const auto& album) {
                               return album->name() == "All Mirrors";
                           }),
              albums.end());
    EXPECT_NE(std::find_if(albums.begin(), albums.end(),
                           [](const auto& album) {
                               return album->name() == "Big Time";
                           }),
              albums.end());

    const auto genres = m_library->genres();
    ASSERT_EQ(genres.size(), 2);
    EXPECT_EQ(genres.at(0), "Americana");
    EXPECT_EQ(genres.at(1), "Art Pop");
}

TEST_F(LibraryServiceTest, SongsAndAlbumsByPerformer) {
    m_library->importTrack({.m_path = "/home/user/Music/all-mirrors/lark.mp3",
                            .m_title = "Lark",
                            .m_performer = "Angel Olsen",
                            .m_album = "All Mirrors",
                            .m_genre = "Art Pop",
                            .m_year = 2019,
                            .m_trackNumber = 1});
    m_library->importTrack(
        {.m_path = "/home/user/Music/big-time/all-the-good-times.mp3",
         .m_title = "All the Good Times",
         .m_performer = "Angel Olsen",
         .m_album = "Big Time",
         .m_genre = "Americana",
         .m_year = 2022,
         .m_trackNumber = 1});
    m_library->importTrack({.m_path = "/home/user/Music/souvlaki/alison.mp3",
                            .m_title = "Alison",
                            .m_performer = "Slowdive",
                            .m_album = "Souvlaki",
                            .m_genre = "Shoegaze",
                            .m_year = 1993,
                            .m_trackNumber = 1});

    const auto angel = m_performers->find("Angel Olsen");
    ASSERT_NE(angel, nullptr);

    const auto songs = m_library->songsByPerformer(angel->id());
    ASSERT_EQ(songs.size(), 2);
    EXPECT_EQ(songs.at(0)->title(), "All the Good Times");
    EXPECT_EQ(songs.at(1)->title(), "Lark");

    const auto albums = m_library->albumsByPerformer(angel->id());
    ASSERT_EQ(albums.size(), 2);
    EXPECT_EQ(albums.at(0)->name(), "All Mirrors");
    EXPECT_EQ(albums.at(1)->name(), "Big Time");
}