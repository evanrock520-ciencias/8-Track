#pragma once

#include "domain/Stats.hpp"
#include "domain/repositories/IAlbumRepository.hpp"
#include "domain/repositories/IPerformerRepository.hpp"
#include "domain/repositories/ISongRepository.hpp"
#include "miner/Miner.hpp"
#include "services/LibraryService.hpp"

namespace Track8::Services {

class LibraryService {
public:
    LibraryService(
        const std::shared_ptr<Repositories::IAlbumRepository>& albums,
        const std::shared_ptr<Repositories::IPerformerRepository>& performers,
        const std::shared_ptr<Repositories::ISongRepository>& songs);
    ~LibraryService() = default;

    /**
     * @brief Escanea un directorio y guarda todos sus metadatos en la base de
     * datos de la aplicación.
     * @param path La ruta del directorio a escanear.
     */
    void scan(const std::filesystem::path& path) const;

    /**
     * Guarda la metadata de una canción en la base de datos.
     * @param metadata Los metadatos relacionadaos a una canción.
     */
    void importTrack(const Track8::Miner::Metadata& metadata) const;

    /**
     * Regresa las canciones de la base de datos.
     * @return Las canciones de la base de datos.
     */
    [[nodiscard]] std::vector<std::shared_ptr<Domain::Song>> songs() const;

    /**
     * Regresa las estadisticas de todos los repositorios.
     * @return Las estadisticas de todos los repositorios.
     */
    [[nodiscard]] Domain::Stats stats() const;

private:
    [[nodiscard]] std::shared_ptr<Domain::Performer>
    findOrCreatePerformer(const std::string& name) const;
    [[nodiscard]] std::shared_ptr<Domain::Album>
    findOrCreateAlbum(const std::string& name, const std::filesystem::path& dir,
                      int year) const;

    std::shared_ptr<Repositories::IAlbumRepository> m_albums;
    std::shared_ptr<Repositories::ISongRepository> m_songs;
    std::shared_ptr<Repositories::IPerformerRepository> m_performers;
};

} // namespace Track8::Services
