#include "gtest/gtest.h"

#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"

using namespace Track8::Database;

class SQLiteSongRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_manager = std::make_unique<DatabaseManager>(":memory:");
        const auto database = m_manager->database();
        m_performers = std::make_shared<SQLitePerformerRepository>(database);
        m_albums = std::make_shared<SQLiteAlbumRepository>(database);
        m_songs = std::make_shared<SQLiteSongRepository>(database, m_performers,
                                                         m_albums);
    }

    void TearDown() override {
        m_songs.reset();
        m_albums.reset();
        m_performers.reset();
        m_manager.reset();
    }

    std::unique_ptr<DatabaseManager> m_manager;
    std::shared_ptr<SQLitePerformerRepository> m_performers;
    std::shared_ptr<SQLiteAlbumRepository> m_albums;
    std::shared_ptr<SQLiteSongRepository> m_songs;
};

TEST_F(SQLiteSongRepositoryTest, CreateSongWithUnregisteredPerformer) {
    using namespace Track8::Domain;
    const auto angelOlsen = std::make_shared<Performer>(1, "Angel Olsen");
    const int allMirrorsId = m_albums->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});

    const auto allMirrors = m_albums->find(allMirrorsId);

    SongBuilder builder;
    const Song lark = builder.with_performer(angelOlsen)
                          .with_album(allMirrors)
                          .with_genre("Art Pop")
                          .with_id(1)
                          .with_path(allMirrors->path() / "lark.mp3")
                          .with_title("Lark")
                          .with_track(1)
                          .with_year(2019)
                          .create();

    EXPECT_ANY_THROW(m_songs->save(lark));
}

TEST_F(SQLiteSongRepositoryTest, CreateSongWithUnregisteredAlbum) {
    using namespace Track8::Domain;
    const int angelOlsenId = m_performers->save("Angel Olsen");
    const auto allMirrors = std::make_shared<Album>(
        1, "/home/user/Music/all-mirrors", "All Mirrors", 2019);

    const auto angelOlsen = m_performers->find(angelOlsenId);

    SongBuilder builder;
    const Song lark = builder.with_performer(angelOlsen)
                          .with_album(allMirrors)
                          .with_genre("Art Pop")
                          .with_id(1)
                          .with_path(allMirrors->path() / "lark.mp3")
                          .with_title("Lark")
                          .with_track(1)
                          .with_year(2019)
                          .create();

    EXPECT_ANY_THROW(m_songs->save(lark));
}

TEST_F(SQLiteSongRepositoryTest, FindSongWithId) {
    using namespace Track8::Domain;
    const int angelOlsenId = m_performers->save("Angel Olsen");
    const int allMirrorsId = m_albums->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});

    const auto angelOlsen = m_performers->find(angelOlsenId);
    const auto allMirrors = m_albums->find(allMirrorsId);

    SongBuilder builder;
    const Song lark = builder.with_performer(angelOlsen)
                          .with_album(allMirrors)
                          .with_genre("Art Pop")
                          .with_id(1)
                          .with_path(allMirrors->path() / "lark.mp3")
                          .with_title("Lark")
                          .with_track(1)
                          .with_year(2019)
                          .create();

    const auto larkId = m_songs->save(lark);
    const auto larkRepo = m_songs->find(larkId);
    ASSERT_EQ(*larkRepo, lark);
}

TEST_F(SQLiteSongRepositoryTest, FindSongWithPath) {
    using namespace Track8::Domain;
    const int angelOlsenId = m_performers->save("Angel Olsen");
    const int allMirrorsId = m_albums->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});

    const auto angelOlsen = m_performers->find(angelOlsenId);
    const auto allMirrors = m_albums->find(allMirrorsId);

    SongBuilder builder;
    const Song lark = builder.with_performer(angelOlsen)
                          .with_album(allMirrors)
                          .with_genre("Art Pop")
                          .with_id(1)
                          .with_path(allMirrors->path() / "lark.mp3")
                          .with_title("Lark")
                          .with_track(1)
                          .with_year(2019)
                          .create();

    const auto _ = m_songs->save(lark);
    const auto larkRepo =
        m_songs->find("/home/user/Music/all-mirrors/lark.mp3");
    ASSERT_EQ(*larkRepo, lark);
}

TEST_F(SQLiteSongRepositoryTest, RemoveSong) {
    using namespace Track8::Domain;
    const int angelOlsenId = m_performers->save("Angel Olsen");
    const int allMirrorsId = m_albums->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});

    const auto angelOlsen = m_performers->find(angelOlsenId);
    const auto allMirrors = m_albums->find(allMirrorsId);

    SongBuilder builder;
    const Song lark = builder.with_performer(angelOlsen)
                          .with_album(allMirrors)
                          .with_genre("Art Pop")
                          .with_id(1)
                          .with_path(allMirrors->path() / "lark.mp3")
                          .with_title("Lark")
                          .with_track(1)
                          .with_year(2019)
                          .create();

    const auto larkId = m_songs->save(lark);
    const auto initialAll = m_songs->getAll();
    ASSERT_EQ(initialAll.size(), 1);

    m_songs->remove(larkId);
    const auto afterAll = m_songs->getAll();
    ASSERT_EQ(afterAll.size(), 0);
}

TEST_F(SQLiteSongRepositoryTest, UpdateSong) {
    using namespace Track8::Domain;
    const int angelOlsenId = m_performers->save("Angel Olsen");
    const int allMirrorsId = m_albums->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});

    const auto angelOlsen = m_performers->find(angelOlsenId);
    const auto allMirrors = m_albums->find(allMirrorsId);

    SongBuilder builder;
    const Song wrongLark = builder.with_performer(angelOlsen)
                               .with_album(allMirrors)
                               .with_genre("Chamber Pop")
                               .with_id(1)
                               .with_path(allMirrors->path() / "larky.mp3")
                               .with_title("Larky")
                               .with_track(1)
                               .with_year(2020)
                               .create();
    const Song lark = builder.with_performer(angelOlsen)
                          .with_album(allMirrors)
                          .with_genre("Art Pop")
                          .with_id(1)
                          .with_path(allMirrors->path() / "lark.mp3")
                          .with_title("Lark")
                          .with_track(1)
                          .with_year(2019)
                          .create();

    const auto larkId = m_songs->save(wrongLark);
    m_songs->update(lark);
    const auto larkRepo = m_songs->find(larkId);

    ASSERT_EQ(lark, *larkRepo);
}

TEST_F(SQLiteSongRepositoryTest, GetAllWithSamePerformer) {
    using namespace Track8::Domain;
    constexpr int SONGS = 100;
    const int angelOlsenId = m_performers->save("Angel Olsen");
    const int allMirrorsId = m_albums->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});

    const auto angelOlsen = m_performers->find(angelOlsenId);
    const auto allMirrors = m_albums->find(allMirrorsId);

    SongBuilder builder;
    for (int id = 1; id < SONGS + 1; id++) {
        const auto song = builder.with_performer(angelOlsen)
                              .with_album(allMirrors)
                              .with_title("Song" + std::to_string(id))
                              .with_id(id)
                              .create();
        m_songs->save(song);
    }

    const auto all = m_songs->getAll();
    ASSERT_EQ(all.size(), SONGS);

    for (int id = 1; id < SONGS + 1; id++) {
        const auto song = builder.with_performer(angelOlsen)
                              .with_album(allMirrors)
                              .with_title("Song" + std::to_string(id))
                              .with_id(id)
                              .create();
        const auto songRepo = m_songs->find(id);
        ASSERT_EQ(*songRepo, song);
    }
}