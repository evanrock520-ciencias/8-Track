#include "gtest/gtest.h"

#include "database/DatabaseManager.hpp"
#include "database/SQLitePerformerRepository.hpp"

using namespace Track8::Database;

class SQLitePerformerRepositoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_manager = std::make_unique<DatabaseManager>(":memory:");
        m_repository =
            std::make_unique<SQLitePerformerRepository>(m_manager->database());
    }

    void TearDown() override {
        m_repository.reset();
        m_manager.reset();
    }

    std::unique_ptr<DatabaseManager> m_manager;
    std::unique_ptr<SQLitePerformerRepository> m_repository;
};

TEST_F(SQLitePerformerRepositoryTest, SavePerformer) {
    using namespace Track8::Domain;
    const int id = m_repository->save("David Bowie");
    const auto saved = m_repository->find(id);

    ASSERT_EQ(id, 1);
}

TEST_F(SQLitePerformerRepositoryTest, FindPerformerWithId) {
    using namespace Track8::Domain;
    const int id = m_repository->save("David Bowie");
    const auto saved = m_repository->find(id);

    ASSERT_EQ(typeid(*saved), typeid(Performer));
    const Performer performer(id, "David Bowie");
    ASSERT_EQ(performer, *saved);
}

TEST_F(SQLitePerformerRepositoryTest, FindPerfomerWithName) {
    using namespace Track8::Domain;
    const int id = m_repository->save("David Bowie");
    const auto saved = m_repository->find("David Bowie");

    ASSERT_EQ(typeid(*saved), typeid(Performer));
    const Performer performer(id, "David Bowie");
    ASSERT_EQ(performer, *saved);
}

TEST_F(SQLitePerformerRepositoryTest, FindArtistWithId) {
    using namespace Track8::Domain;
    const int id = m_repository->save("David Bowie");
    m_repository->markAsArtist(id);

    const auto saved = m_repository->find(id);
    ASSERT_EQ(typeid(*saved), typeid(Artist));

    const Artist artist(1, "David Bowie", "Unknown", Date("0000-00-00"),
                        Date("0000-00-00"));
    ASSERT_EQ(artist, *saved);
}

TEST_F(SQLitePerformerRepositoryTest, FindArtistWithName) {
    using namespace Track8::Domain;
    const int id = m_repository->save("David Bowie");
    m_repository->markAsArtist(id);

    const auto saved = m_repository->find(id);
    ASSERT_EQ(typeid(*saved), typeid(Artist));

    const Artist artist(1, "David Bowie", "Unknown", Date("0000-00-00"),
                        Date("0000-00-00"));
    ASSERT_EQ(artist, *saved);
}

TEST_F(SQLitePerformerRepositoryTest, FindGroupWithId) {
    using namespace Track8::Domain;
    const int id = m_repository->save("King Crimson");
    m_repository->markAsGroup(id);

    const auto saved = m_repository->find(id);
    ASSERT_EQ(typeid(*saved), typeid(Group));

    const Group group(1, "King Crimson", Date("0000-00-00"),
                      Date("0000-00-00"));
    ASSERT_EQ(group, *saved);
}

TEST_F(SQLitePerformerRepositoryTest, FindGroupWithName) {
    using namespace Track8::Domain;
    const int id = m_repository->save("King Crimson");
    m_repository->markAsGroup(id);

    const auto saved = m_repository->find(id);
    ASSERT_EQ(typeid(*saved), typeid(Group));

    const Group group(1, "King Crimson", Date("0000-00-00"),
                      Date("0000-00-00"));
    ASSERT_EQ(group, *saved);
}