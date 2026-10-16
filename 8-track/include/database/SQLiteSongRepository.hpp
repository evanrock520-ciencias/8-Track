#pragma once
#include "domain/repositories/ISongRepository.hpp"

using namespace Track8::Repositories;

namespace Track8::Database {

/**
 * @class SQLiteSongRepository
 * @brief Implementación de @ref ISongRepository para SQLite.
 */
class SQLiteSongRepository : public ISongRepository {
public:
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
};
} // namespace Track8::Database