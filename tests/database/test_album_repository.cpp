#include "database/DatabaseManager.hpp"
#include "database/SQLiteAlbumRepository.hpp"
#include <gtest/gtest.h>

#include <QCoreApplication>

using namespace Track8::Database;

class SQLiteAlbumRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_manager = std::make_unique<DatabaseManager>(":memory:");
        m_repository =
            std::make_unique<SQLiteAlbumRepository>(m_manager->database());
    }

    void TearDown() override {
        m_repository.reset();
        m_manager.reset();
    }

    std::unique_ptr<DatabaseManager> m_manager;
    std::unique_ptr<SQLiteAlbumRepository> m_repository;
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