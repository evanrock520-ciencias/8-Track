#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "database/SQLiteSongRepository.hpp"
#include <gtest/gtest.h>

#include <QCoreApplication>

using namespace Track8::Database;

class SQLiteAlbumRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_manager = std::make_unique<DatabaseManager>(":memory:");
        const auto database = m_manager->database();
        m_repository = std::make_shared<SQLiteAlbumRepository>(database);
        m_performers = std::make_shared<SQLitePerformerRepository>(database);
        m_songs = std::make_shared<SQLiteSongRepository>(database, m_performers,
                                                         m_repository);
    }

    void TearDown() override {
        m_songs.reset();
        m_performers.reset();
        m_repository.reset();
        m_manager.reset();
    }

    std::unique_ptr<DatabaseManager> m_manager;
    std::shared_ptr<SQLiteAlbumRepository> m_repository;
    std::shared_ptr<SQLitePerformerRepository> m_performers;
    std::shared_ptr<SQLiteSongRepository> m_songs;
};

TEST_F(SQLiteAlbumRepositoryTest, SaveAlbum) {
    using namespace Track8::Domain;
    const Album album(1, "/home/user/Music/big-time", "Big Time", 2022);
    const int id = m_repository->save(album);

    EXPECT_EQ(id, 1);
}

TEST_F(SQLiteAlbumRepositoryTest, FindWithId) {
    using namespace Track8::Domain;
    const Album album(1, "/home/user/Music/big-time", "Big Time", 2022);
    const int id = m_repository->save(album);

    const auto saved = m_repository->find(id);
    ASSERT_NE(saved, nullptr);
    ASSERT_EQ(album, *saved);
}

TEST_F(SQLiteAlbumRepositoryTest, FindWithPathAndName) {
    using namespace Track8::Domain;
    const Album album(1, "/home/user/Music/big-time", "Big Time", 2022);
    m_repository->save(album);

    const auto saved =
        m_repository->find("Big Time", "/home/user/Music/big-time");
    ASSERT_NE(saved, nullptr);
    ASSERT_EQ(album, *saved);
}

TEST_F(SQLiteAlbumRepositoryTest, UpdateAlbum) {
    using namespace Track8::Domain;
    const Album bigTime(1, "/home/user/Music/big-time", "Big Time", 2022);
    const int id = m_repository->save(bigTime);

    const Album allMirrors(1, "/home/user/Music/all-mirrors", "All Mirrors",
                           2019);
    m_repository->update(allMirrors);

    const auto saved = m_repository->find(id);
    ASSERT_NE(saved, nullptr);
    ASSERT_EQ(allMirrors, *saved);
}

TEST_F(SQLiteAlbumRepositoryTest, GetAlbumsByPerformer) {
    using namespace Track8::Domain;

    const int angelOlsenId = m_performers->save("Angel Olsen");
    const int slowdiveId = m_performers->save("Slowdive");

    const auto angelOlsen = m_performers->find(angelOlsenId);
    const auto slowdive = m_performers->find(slowdiveId);
    ASSERT_NE(angelOlsen, nullptr);
    ASSERT_NE(slowdive, nullptr);

    const int allMirrorsId = m_repository->save(
        {1, "/home/user/Music/all-mirrors", "All Mirrors", 2019});
    const int bigTimeId =
        m_repository->save({2, "/home/user/Music/big-time", "Big Time", 2022});
    const int souvlakiId =
        m_repository->save({3, "/home/user/Music/souvlaki", "Souvlaki", 1993});

    const auto allMirrors = m_repository->find(allMirrorsId);
    const auto bigTime = m_repository->find(bigTimeId);
    const auto souvlaki = m_repository->find(souvlakiId);

    SongBuilder builder;
    m_songs->save(builder.with_performer(angelOlsen)
                      .with_album(allMirrors)
                      .with_title("Lark")
                      .with_path("/home/user/Music/all-mirrors/lark.mp3")
                      .create());
    m_songs->save(
        builder.with_performer(angelOlsen)
            .with_album(bigTime)
            .with_title("All the Good Times")
            .with_path("/home/user/Music/big-time/all-the-good-times.mp3")
            .create());
    m_songs->save(builder.with_performer(slowdive)
                      .with_album(souvlaki)
                      .with_title("Alison")
                      .with_path("/home/user/Music/souvlaki/alison.mp3")
                      .create());

    const auto albums = m_repository->getByPerformer(angelOlsenId);
    ASSERT_EQ(albums.size(), 2);
    EXPECT_EQ(albums.at(0)->name(), "All Mirrors");
    EXPECT_EQ(albums.at(1)->name(), "Big Time");

    EXPECT_TRUE(m_repository->getByPerformer(1224).empty());
}

TEST_F(SQLiteAlbumRepositoryTest, GetAll) {
    using namespace Track8::Domain;
    constexpr int ALBUMS = 100;
    for (int id = 1; id < ALBUMS; id++) {
        const Album album(id, "/home/user/Music/Album" + std::to_string(id),
                          "Album" + std::to_string(id), 1920 + id);
        m_repository->save(album);
    }

    const auto albums = m_repository->getAll();
    ASSERT_EQ(albums.size(), ALBUMS);

    for (const auto& album : albums) {
        const int id = album->id();
        const auto other = m_repository->find(id);
        ASSERT_EQ(*album, *other);
    }
}