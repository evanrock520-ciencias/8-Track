#pragma once
#include "services/LibraryService.hpp"

namespace Track8::Cli {

/**
 * @brief Representación el flujo de ejecución por terminal.
 */
class Cli {
public:
    explicit Cli(Services::LibraryService& library);

    /**
     * Corre la interfaz de comandos para 8-track.
     * @param argc El contandor de argumentos del programa.
     * @param argv Los argumentos del programa.
     */
    void run(int argc, char** argv);

private:
    /**
     * Muestra una tabla con todas las canciones que cumplen la especificación
     * de la query.
     * @param rawQuery Una cadena cruda con la especificación MuQL.
     */
    void query(const std::string& rawQuery);

    /**
     * Muestra una tabla con todas las canciones de la base de datos.
     */
    void list() const;

    Services::LibraryService& m_library;
};

} // namespace Track8::Cli