#pragma once
#include "services/ArtistService.hpp"
#include "services/LibraryService.hpp"
#include "services/SearchService.hpp"

namespace Track8::Cli {

/**
 * @brief Representación el flujo de ejecución por terminal.
 */
class Cli {
public:
    Cli(Services::LibraryService& library, Services::SearchService& search,
        Services::ArtistService& artists);

    /**
     * Corre la interfaz de comandos para 8-track.
     * @param argc El contandor de argumentos del programa.
     * @param argv Los argumentos del programa.
     */
    void run(int argc, char** argv) const;

private:
    /**
     * Muestra una tabla con todas las canciones que cumplen la especificación
     * de la query.
     * @param rawQuery Una cadena cruda con la especificación MuQL.
     */
    void queryTable(const std::string& rawQuery) const;

    /**
     * Muestra una tabla con todas las canciones de la base de datos.
     */
    void list() const;

    Services::LibraryService& m_library;
    Services::SearchService& m_search;
    Services::ArtistService& m_artists;
};

} // namespace Track8::Cli