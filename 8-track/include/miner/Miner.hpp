#pragma once
#include "Metadata.hpp"

#include <filesystem>
#include <functional>

namespace Track8::Miner {
class Miner {
public:
    explicit Miner(std::filesystem::path path);
    ~Miner() = default;

    /**
     * @brief Escanea el directorio configurado recursivamente para obtener
     * `tags` de archivos `.mp3`.
     * @param callback Función invocable que se ejecuta por cada archivo
     * procesado exitosamente.
     */
    void mine(const std::function<void(const Metadata&)>& callback) const;

private:
    /**
     * @brief Obtiene los metadatos de un archivo `.mp3`.
     * @param path La ruta de un archivo `mp3`.
     * @return Los metadatos relacionados al archivo `.mp3`.
     */
    static Metadata parseFile(const std::filesystem::path& path);

    std::filesystem::path m_path;
};
} // namespace Track8::Miner