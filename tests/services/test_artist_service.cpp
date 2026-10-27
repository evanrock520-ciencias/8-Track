#include "gtest/gtest.h"

#include "database/DatabaseManager.hpp"
#include "database/SQLitePerformerRepository.hpp"
#include "domain/Artist.hpp"
#include "domain/Group.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "services/ArtistService.hpp"

#include <memory>
#include <stdexcept>

using namespace Track8;

class ArtistServiceTest : public ::testing::Test {
protected:
    void SetUp() override {
        m_manager = std::make_unique<Database::DatabaseManager>(":memory:");
        m_performers = std::make_shared<Database::SQLitePerformerRepository>(
            m_manager->database());
        m_service = std::make_unique<Services::ArtistService>(m_performers);
    };

    void TearDown() override {
        m_service.reset();
        m_performers.reset();
        m_manager.reset();
    }

    std::unique_ptr<Services::ArtistService> m_service;
    std::unique_ptr<Database::DatabaseManager> m_manager;
    std::shared_ptr<IPerformerRepository> m_performers;
};

TEST_F(ArtistServiceTest, MarkAsPersonByName) {
    const int id = m_performers->save("Angel Olsen");

    m_service->markAsPerson("Angel Olsen");

    const auto performer = m_performers->find(id);
    ASSERT_NE(performer, nullptr);
    ASSERT_EQ(typeid(*performer), typeid(Domain::Artist));
}

TEST_F(ArtistServiceTest, MarkAsGroupByName) {
    const int id = m_performers->save("Slowdive");

    m_service->markAsGroup("Slowdive");

    const auto performer = m_performers->find(id);
    ASSERT_NE(performer, nullptr);
    ASSERT_EQ(typeid(*performer), typeid(Domain::Group));
}

TEST_F(ArtistServiceTest, MarkAsPersonByNameNotFound) {
    ASSERT_THROW(m_service->markAsPerson("Fraçoise Hardy"), std::runtime_error);
}

TEST_F(ArtistServiceTest, MarkAsGroupByNameNotFound) {
    ASSERT_THROW(m_service->markAsGroup("Florence and the Machine"),
                 std::runtime_error);
}

TEST_F(ArtistServiceTest, FindByName) {
    const int id = m_performers->save("Nico");

    const auto performer = m_service->find("Nico");

    ASSERT_NE(performer, nullptr);
    ASSERT_EQ(performer->id(), id);
    ASSERT_EQ(performer->name(), "Nico");
}

TEST_F(ArtistServiceTest, FindById) {
    const int id = m_performers->save("Nico");

    const auto performer = m_service->find(id);

    ASSERT_NE(performer, nullptr);
    ASSERT_EQ(performer->id(), id);
}

TEST_F(ArtistServiceTest, FindMissingReturnsNull) {
    ASSERT_EQ(m_service->find("Nico"), nullptr);
    ASSERT_EQ(m_service->find(1224), nullptr);
}

TEST_F(ArtistServiceTest, MembersOfMissingGroupIsEmpty) {
    ASSERT_TRUE(m_service->members(1224).empty());
}
