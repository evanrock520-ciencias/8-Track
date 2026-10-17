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