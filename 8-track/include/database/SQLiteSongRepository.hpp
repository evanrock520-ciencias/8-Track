#pragma once
#include "domain/repositories/ISongRepository.hpp"

#include <QSqlDatabase>

using namespace Track8::Repositories;

namespace Track8::Database {

/**
 * @class SQLiteSongRepository
 * @brief Implementación de @ref ISongRepository para SQLite.
 */
class SQLiteSongRepository : public ISongRepository {
public:
    explicit SQLiteSongRepository(QSqlDatabase database);
    ~SQLiteSongRepository() override = default;

    int save(const Domain::Song& song) override;

    std::shared_ptr<Domain::Song>
    find(const std::filesystem::path& path) override;

    std::shared_ptr<Domain::Song> find(int id) override;

    std::vector<std::shared_ptr<Domain::Song>>
    find(const Compiler::Query& query) override;

    void update(const Domain::Song& song) override;

    void remove(int id) override;

    std::vector<std::shared_ptr<Domain::Song>> getAll() override;

private:
    QSqlDatabase m_database;
};
} // namespace Track8::Database