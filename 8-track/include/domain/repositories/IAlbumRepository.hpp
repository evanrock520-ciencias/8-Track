#pragma once
#include "../Album.hpp"

#include <vector>

namespace Track8::Repositories {

/**
 * @class IAlbumRepository
 * @brief Interfaz del repository que administra y mantiene la comunicación con
 * las tabla de ´albums`.
 */
class IAlbumRepository {
public:
    virtual ~IAlbumRepository() = default;

    /**
     * Agrega un álbum a la base de datos.
     * @param album El álbum añadido.
     * @return El id del álbum en la tabla de `albums`.
     */
    virtual int save(const Domain::Album& album) = 0;

    /**
     * Busca un álbum a partir de su nombre y ruta.
     * @param name El nombre relacionado al álbum.
     * @param path La ruta relacionada al álbum.
     * @return El álbum relacionado al `nombre` y `path`
     */
    virtual std::shared_ptr<Domain::Album>
    find(const std::string& name, const std::filesystem::path& path) = 0;

    /**
     * Busca el álbum a partir de su id.
     * @param id El id del álbum en la tabla de `albums`.
     * @return El álbum relacionado al id.
     */
    virtual std::shared_ptr<Domain::Album> find(int id) = 0;

    /**
     * Actualiza un albúm en la base de datos.
     * @param album El álbum actualizado.
     */
    virtual void update(const Domain::Album& album) = 0;

    /**
     * Regresa todos los álbums en la base de datos.
     * @return Todos los álbums en la base de datos.
     */
    virtual std::vector<std::shared_ptr<Domain::Album>> getAll() = 0;
};
} // namespace Track8::Repositories