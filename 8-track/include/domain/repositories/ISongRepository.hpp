#pragma once
#include "compiler/Token.hpp"
#include "domain/Song.hpp"

#include <vector>

// Forward Definition
namespace Track8::Compiler {
// TODO: Implementar las Query
class Query;
} // namespace Track8::Compiler

namespace Track8::Repositories {

/**
 * @class ISongRepository
 * @brief Interfaz del repository que administra y mantiene la comunicación con
 * las tabla de ´rolas`.
 */
class ISongRepository {
public:
    virtual ~ISongRepository() = default;

    /**
     * Agrega una canción a la base de datos.
     * @param song La canción agregada al repositorio.
     * @return El id de la canción el tabla de `rolas`
     */
    virtual int save(const Domain::Song& song) = 0;

    /**
     * Busca una canción relacionada a una ruta del sistema.
     * @param path La ruta del archivo mp3 relacionado a la canción.
     * @return La canción relacionada al `path`.
     */
    virtual std::shared_ptr<Domain::Song>
    find(const std::filesystem::path& path) = 0;

    /**
     *
     * @param id El id de la `canción` en la tabla de `rolas`.
     * @return La canción relacionada al `id`.
     */
    virtual std::shared_ptr<Domain::Song> find(int id) = 0;

    /**
     * Busca canciones que cumplan las especificaciones de un `Compiler::Query`.
     * @param query La especificación de búsqueda. Está relacionada al módulo de
     * `Compiler`.
     * @return Las canciones que cumplen las especificación del `query`.
     */
    virtual std::vector<std::shared_ptr<Domain::Song>>
    find(const Compiler::Query& query) = 0;

    /**
     * Actualiza una canción en la base de datos.
     * @param song La canción actualizada.
     */
    virtual void update(const Domain::Song& song) = 0;

    /**
     * Elimina una canción de la base de datos.
     * @param id El id de la canción en la tabla de `rolas`
     */
    virtual void remove(int id) = 0;

    /**
     * Regresa todas las canciones de la base de datos.
     * @return Todas las canciones de la base de datos.
     */
    virtual std::vector<std::shared_ptr<Domain::Song>> getAll() = 0;

    /**
     * Regresa la cantidad de rolas en la base de datos.
     * @return La cantidad de rolas en la base de datos.
     */
    virtual unsigned int count() = 0;
};
} // namespace Track8::Repositories