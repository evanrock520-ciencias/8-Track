#pragma once
#include "domain/Song.hpp"

#include <memory>
#include <tabulate/table.hpp>
#include <vector>

namespace Track8::Cli {

/**
 * @brief Wrapper sobre @ref tabulate para tabular las tablas de canciones
 * en consola.
 */
class Tabulator {
public:
    /**
     * Regresa una tabla formateada con las canciones.
     * @param songs Las canciones a mostrar.
     * @return La tabla formateada con las canciones.
     */
    [[nodiscard]] static tabulate::Table
    tabulate(const std::vector<std::shared_ptr<Domain::Song>>& songs);
};

} // namespace Track8::Cli