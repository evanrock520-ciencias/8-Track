#pragma once
#include "domain/repositories/IAlbumRepository.hpp"

#include <QSqlDatabase>

using namespace Track8::Repositories;

namespace Track8::Database {

/**
 * @class SQLiteAlbumRepository
 * @brief Implementación de @ref IAlbumRepository para SQLite.
 */
class SQLiteAlbumRepository : public IAlbumRepository {
public:
    explicit SQLiteAlbumRepository(const QSqlDatabase& database);
    ~SQLiteAlbumRepository() override = default;

    int save(const Domain::Album& album) override;

    std::shared_ptr<Domain::Album>
    find(const std::string& name, const std::filesystem::path& path) override;

    std::shared_ptr<Domain::Album> find(int id) override;

    void update(const Domain::Album& album) override;

    std::vector<std::shared_ptr<Domain::Album>> getAll() override;

private:
    QSqlDatabase m_database;
};
} // namespace Track8::Database