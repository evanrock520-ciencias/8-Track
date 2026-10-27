#pragma once
#include "../Artist.hpp"
#include "../Group.hpp"
#include "../Performer.hpp"

#include <memory>
#include <string>

namespace Track8::Repositories {

/**
 * @class IPerformerRepository
 * @brief Interfaz del repository que administra y mantiene la comunicación con
 * las tablas de `performers`, `persons` y `groups`.
 */
class IPerformerRepository {
public:
    virtual ~IPerformerRepository() = default;

    /**
     * Agrega un interpréte a la base de datos.
     * @param name El nombre del intérprete.
     * @return El índice del intérprete en la tabla de `performers`.
     */
    virtual int save(const std::string& name) = 0;

    /**
     * Encuentra un intérprete por su nombre.
     * @param name El nombre del intérprete.
     * @return El intérprete relacionado al nombre.
     */
    virtual std::shared_ptr<Domain::Performer>
    find(const std::string& name) = 0;

    /**
     * Encuentra un intérprete por id.
     * @param id El id del intérprete
     * @return El intérprete relacionado al id.
     */
    virtual std::shared_ptr<Domain::Performer> find(int id) = 0;

    /**
     * Marca como grupo o banda a un intérprete.
     * @param id El id del intérprte en la tabla de `performers`.
     */
    virtual void markAsGroup(int id) = 0;

    /**
     * Marca como artista (persona) a un intérprete.
     * @param id El id del intérprte en la tabla de `performers`.
     */
    virtual void markAsArtist(int id) = 0;

    /**
     * Añade a un artista como miembro de una banda.
     * @param groupId El id de la banda en la tabla de `performers`.
     * @param performerId El id del artista en la tabla de `performers`.
     */
    virtual void addToGroup(int groupId, int performerId) = 0;

    /**
     * Elimina a un artista como miembro de una banda.
     * @param groupId El id de la banda en la tabla de `performers`.
     * @param performerId El id del artista en la tabla de `performers`.
     */
    virtual void removeFromGroup(int groupId, int performerId) = 0;

    /**
     * Regresa los miembros de una banda.
     * @param groupId El id de la banda en la tabla de `performers`.
     * @return Los miembros de una banda.
     */
    virtual std::vector<std::shared_ptr<Domain::Artist>>
    getMembers(int groupId) = 0;

    /**
     * Regresa los grupos a los que pertenece un artista.
     * @param personId El id del artista en la tabla de `performers`.
     * @return Los grupos del artista.
     */
    virtual std::vector<std::shared_ptr<Domain::Group>>
    getGroups(int personId) = 0;

    /**
     * Regresa la cantidad de intérpretes de un tipo específico.
     * @param type El tipo de intérprete.
     * @return La cantidad de intérpretes de ese tipo.
     */
    virtual unsigned int countByType(Domain::PerformerType type) = 0;

    /**
     * Actualiza a un intérprete en la base de datos.
     * @param performer El intérprete actualizado.
     */
    virtual void update(const Domain::Performer& performer) = 0;

    /**
     * Actualiza a un artista en la base de datos.
     * @param artist El artista actualizado.
     */
    virtual void update(const Domain::Artist& artist) = 0;

    /**
     * Actualiza a una banda en la base de datos.
     * @param group La banda actualizada.
     */
    virtual void update(const Domain::Group& group) = 0;

    /**
     * Regresa todos los intérpretes de la base de datos.
     * @return Todos los intérpretes de la base de datos.
     */
    virtual std::vector<std::shared_ptr<Domain::Performer>> getAll() = 0;

    /**
     * Regresa la cantidad de intérpretes en la base de datos.
     * @return La cantidad de intérpretes en la base de datos.
     */
    virtual unsigned int count() = 0;
};
} // namespace Track8::Repositories