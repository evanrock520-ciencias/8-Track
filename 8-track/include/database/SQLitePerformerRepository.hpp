#pragma once
#include "domain/repositories/IPerformerRepository.hpp"

#include <QSqlDatabase>

#include <optional>
#include <string>

using namespace Track8::Repositories;

namespace Track8::Database {

/**
 * @class SQLitePerformerRepository
 * @brief Implementación de @ref IPerformerRepository para SQLite.
 */
class SQLitePerformerRepository : public IPerformerRepository {
public:
    explicit SQLitePerformerRepository(const QSqlDatabase& database);
    ~SQLitePerformerRepository() override = default;

    int save(const std::string& name) override;

    std::shared_ptr<Domain::Performer> find(const std::string& name) override;

    std::shared_ptr<Domain::Performer> find(int id) override;

    void markAsGroup(int id) override;

    void markAsArtist(int id) override;

    void addToGroup(int groupId, int performerId) override;

    void removeFromGroup(int groupId, int performerId) override;

    std::vector<std::shared_ptr<Domain::Artist>>
    getMembers(int groupId) override;

    std::vector<std::shared_ptr<Domain::Group>>
    getGroups(int personId) override;

    unsigned int countByType(Domain::PerformerType type) override;

    void update(const Domain::Performer& performer) override;

    void update(const Domain::Artist& artist) override;

    void update(const Domain::Group& group) override;

    std::vector<std::shared_ptr<Domain::Performer>> getAll() override;

    unsigned int count() override;

private:
    /**
     * Encuentra a un artista de la tabla de `groups`
     * @param id El id del grupo.
     * @return El grupo relacionado al id.
     */
    std::shared_ptr<Domain::Group> findGroup(int id) const;

    /**
     * Encuentra a un artista de la tabla `persons`.
     * @param id El id del artista.
     * @return El artista relacionado al id.
     */
    std::shared_ptr<Domain::Artist> findArtist(int id) const;

    /**
     * Obtiene el nombre de un intérprete.
     * @param id El id del intérprete en la tabla de `performers`.
     * @return El nombre, o `std::nullopt` si el intérprete no existe.
     */
    std::optional<std::string> findName(int id) const;

    QSqlDatabase m_database;
};
} // namespace Track8::Database