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
    void markAsPerson(int id);

    /**
     * Actualiza el tipo de un intérprete a `group`
     * @param id El id del intérprete.
     */
    void markAsGroup(int id);

    /**
     * Actualiza los valores de un intérprete de tipo `person` en la base de
     * datos.
     * @param person La `person` con valores actualizados.
     */
    void updatePerson(Domain::Artist person);

    /**
     * Actualiza los valores de un intérprete de tipo `group` en la base de
     * datos.
     * @param group El `group` con valores actualizados.
     */
    void updateGroup(Domain::Group group);

    /**
     * Añade un miembro a un grupo (relación en la tabla in_group).
     * @param groupId El id del grupo en la tabla de performers.
     * @param personId El id del miembro en la tabla de performers.
     */
    void addMember(int groupId, int personId);

    /**
     * Elimina un miembro de un grupo (relación en la tabla in_group).
     * @param groupId El id del grupo en la tabla de performers.
     * @param personId El id del miembro en la tabla de performers.
     */
    void removeMember(int groupId, int personId);

private:
    std::shared_ptr<Repositories::IPerformerRepository> m_performers;
};

} // namespace Track8::Services