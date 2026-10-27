#pragma once
#include "domain/repositories/IPerformerRepository.hpp"

#include <memory>

namespace Track8::Services {

class ArtistService {
public:
    explicit ArtistService(
        const std::shared_ptr<Repositories::IPerformerRepository>& performers);

    /**
     * Actualiza el tipo de un intérprete a `person`.
     * @param id El id del intérprete.
     */
    void markAsPerson(int id) const;

    /**
     * Actualiza el tipo de un intérprete a `person`.
     * @param name El nombre del intérprete.
     * @throws std::runtime_error Si no existe un intérprete con ese nombre.
     */
    void markAsPerson(const std::string& name) const;

    /**
     * Actualiza el tipo de un intérprete a `group`
     * @param id El id del intérprete.
     */
    void markAsGroup(int id) const;

    /**
     * Actualiza el tipo de un intérprete a `group`.
     * @param name El nombre del intérprete.
     * @throws std::runtime_error Si no existe un intérprete con ese nombre.
     */
    void markAsGroup(const std::string& name) const;

    /**
     * Actualiza los valores de un intérprete de tipo `person` en la base de
     * datos.
     * @param person La `person` con valores actualizados.
     */
    void updatePerson(const Domain::Artist& person) const;

    /**
     * Actualiza los valores de un intérprete de tipo `group` en la base de
     * datos.
     * @param group El `group` con valores actualizados.
     */
    void updateGroup(const Domain::Group& group) const;

    /**
     * Añade un miembro a un grupo (relación en la tabla in_group).
     * @param groupId El id del grupo en la tabla de performers.
     * @param personId El id del miembro en la tabla de performers.
     */
    void addMember(int groupId, int personId) const;

    /**
     * Elimina un miembro de un grupo (relación en la tabla in_group).
     * @param groupId El id del grupo en la tabla de performers.
     * @param personId El id del miembro en la tabla de performers.
     */
    void removeMember(int groupId, int personId) const;

    /**
     * Regresa los performers en la base de datos.
     * @return Los performers en la base de datos.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Domain::Performer>>
    performers() const;

    /**
     * Encuentra el intérprete relacionado a un `id`
     * @param id El id relacionado al intérprete.
     * @return El intérprete relacionado al `id`, o `nullptr` si no existe.
     */
    [[nodiscard]] std::shared_ptr<Domain::Performer> find(int id) const;

    /**
     * Encuentra el intérprete relacionado a un `name`
     * @param name El nombre relacionado al intérprete.
     * @return El intérprete relacionado al `name`, o `nullptr` si no existe.
     */
    [[nodiscard]] std::shared_ptr<Domain::Performer>
    find(const std::string& name) const;

    /**
     * Regresa los miembros de un grupo relacionado a un `id`.
     * @param groupId El `id` del grupo.
     * @return Los miembros del grupo, o un vector vacío si no existe.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Domain::Artist>>
    members(int groupId) const;

    /**
     * Regresa los grupos a los que pertenece un artista.
     * @param personId El id del artista.
     * @return Los grupos del artista.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Domain::Group>>
    groupsOfPerson(int personId) const;

private:
    std::shared_ptr<Repositories::IPerformerRepository> m_performers;
};

} // namespace Track8::Services