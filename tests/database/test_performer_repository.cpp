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

TEST_F(SQLitePerformerRepositoryTest, AddArtistToGroup) {
    using namespace Track8::Domain;

    const int cameronId = m_repository->save("Cameron Winter");
    m_repository->markAsArtist(cameronId);

    const int geeseId = m_repository->save("Geese");
    m_repository->markAsGroup(geeseId);

    m_repository->addToGroup(geeseId, cameronId);
    const auto members = m_repository->getMembers(geeseId);

    ASSERT_EQ(members.size(), 1);
    const auto cameronRepo = m_repository->find(cameronId);
    const auto& cameronGeese = members.at(0);
    ASSERT_EQ(*cameronGeese, *cameronRepo);
}

TEST_F(SQLitePerformerRepositoryTest, AddGroupToGroup) {
    using namespace Track8::Domain;

    const int bcnr = m_repository->save("Black Country New Road");
    m_repository->markAsGroup(bcnr);

    const int kglw = m_repository->save("King Gizzard & the Lizard Wizard");
    m_repository->markAsGroup(kglw);

    EXPECT_ANY_THROW(m_repository->addToGroup(kglw, bcnr));
}

TEST_F(SQLitePerformerRepositoryTest, RemoveArtistFromGroup) {
    using namespace Track8::Domain;

    const int sydId = m_repository->save("Syd Barret");
    m_repository->markAsArtist(sydId);

    const int pinkFloydId = m_repository->save("Pink Floyd");
    m_repository->markAsGroup(pinkFloydId);

    m_repository->addToGroup(pinkFloydId, sydId);
    const auto initialMembers = m_repository->getMembers(pinkFloydId);

    ASSERT_EQ(initialMembers.size(), 1);
    m_repository->removeFromGroup(pinkFloydId, sydId);
    const auto afterMembers = m_repository->getMembers(pinkFloydId);
    ASSERT_EQ(afterMembers.size(), 0);
}

TEST_F(SQLitePerformerRepositoryTest, UpdateArtist) {
    using namespace Track8::Domain;
    const int id = m_repository->save("Angel Olsen");
    m_repository->markAsArtist(id);

    const Artist angelOlsen(id, "Angel Olsen", "Angelina Marie Carroll",
                            Date("1987-01-22"), Date("0000-00-00"));
    m_repository->update(angelOlsen);

    const auto angelOlsenRepo = m_repository->find(id);
    ASSERT_EQ(*angelOlsenRepo, angelOlsen);
}

TEST_F(SQLitePerformerRepositoryTest, UpdateGroup) {
    using namespace Track8::Domain;

    const int id = m_repository->save("On a Friday");
    m_repository->markAsGroup(id);

    const Group radiohead(id, "Radiohead", Date("1985-01-01"),
                          Date("0000-00-00"));
    m_repository->update(radiohead);

    const auto radioheadRepo = m_repository->find(id);
    ASSERT_EQ(*radioheadRepo, radiohead);
}

TEST_F(SQLitePerformerRepositoryTest, UpdatePerformer) {
    using namespace Track8::Domain;
    const int id = m_repository->save("Pumpkin Fairies");
    const Performer slowdive(id, "Slowdive");
    m_repository->update(slowdive);

    const auto slowdiveRepo = m_repository->find(id);
    ASSERT_EQ(*slowdiveRepo, slowdive);
}

TEST_F(SQLitePerformerRepositoryTest, GetAll) {
    using namespace Track8::Domain;
    constexpr int PERFORMERS = 100;

    for (int id = 1; id < PERFORMERS + 1; ++id)
        m_repository->save("Performer" + std::to_string(id));

    const auto all = m_repository->getAll();
    ASSERT_EQ(all.size(), PERFORMERS);

    for (int id = 1; id < PERFORMERS + 1; ++id) {
        const auto performerRepo = m_repository->find(id);
        const Performer performer(id, "Performer" + std::to_string(id));
        ASSERT_EQ(*performerRepo, performer);
    }
}