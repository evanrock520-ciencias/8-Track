#pragma once
#include "domain/repositories/IPerformerRepository.hpp"

#include <QSqlDatabase>

using namespace Track8::Repositories;

namespace Track8::Database {

/**
 * @class SQLitePerformerRepository
 * @brief Implementación de @ref IPerformerRepository para SQLite.
 */
class SQLitePerformerRepository : public IPerformerRepository {
public:
    explicit SQLitePerformerRepository(QSqlDatabase database);
    ~SQLitePerformerRepository() override = default;

    int save(const std::string& name) override;

    std::shared_ptr<Domain::Performer> find(const std::string& name) override;

    void markAsGroup(int id) override;

    void markAsArtist(int id) override;

    void addToGroup(int groupId, int performerId) override;

    void removeFromGroup(int groupId, int performerId) override;

    std::vector<std::shared_ptr<Domain::Artist>>
    getMembers(int groupId) override;

    void update(const Domain::Artist& artist) override;

    void update(const Domain::Group& group) override;

    std::vector<std::shared_ptr<Domain::Performer>> getAll() override;

private:
    QSqlDatabase m_database;
};
} // namespace Track8::Database