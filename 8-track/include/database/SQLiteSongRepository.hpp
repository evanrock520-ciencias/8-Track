#pragma once
#include "domain/repositories/IAlbumRepository.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "domain/repositories/ISongRepository.hpp"

#include <QSqlDatabase>

#include <memory>

class QSqlQuery;

using namespace Track8::Repositories;

namespace Track8::Database {

/**
 * @class SQLiteSongRepository
 * @brief Implementación de @ref ISongRepository para SQLite.
 */
class SQLiteSongRepository : public ISongRepository {
public:
    SQLiteSongRepository(const QSqlDatabase& database,
                         std::shared_ptr<IPerformerRepository> performers,
                         std::shared_ptr<IAlbumRepository> albums);
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

    unsigned int count() override;

private:
    /**
     * @brief Reconstruye una `rola` a partir de los repositorios de performers
     * y álbums.
     * @param query Cursor sobre rola
     * @return La rola reconstruida
     */
    [[nodiscard]] std::shared_ptr<Domain::Song>
    buildSong(const QSqlQuery& query) const;

    QSqlDatabase m_database;
    std::shared_ptr<IAlbumRepository> m_albums;
    std::shared_ptr<IPerformerRepository> m_performers;
};
} // namespace Track8::Database