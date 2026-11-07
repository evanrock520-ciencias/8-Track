#pragma once

#include <filesystem>
#include <functional>

namespace Track8::Player {

enum class PlaybackState { Stopped, Playing, Paused };

/**
 * @class IAudioBackend
 * @brief Interfaz para reproductores de audio.
 */
class IAudioBackend {
public:
    virtual ~IAudioBackend() = default;

    /**
     * Carga el archivo a reproducir.
     * @param path La ruta del archivo a reproducir.
     */
    virtual void load(const std::filesystem::path& path) = 0;

    /**
     * Reproduce la canción actual.
     */
    virtual void play() = 0;

    /**
     * Pausa la canción actual.
     */
    virtual void pause() = 0;

    /**
     * Detiene la reproducción.
     */
    virtual void stop() = 0;

    /**
     * Establece el volumen de salida.
     * @param volume El nuevo volumen de salida.
     */
    virtual void setVolume(float volume) = 0;

    /**
     * Mueve el tiempo de reproducción de la canción.
     * @param positionMs El nuevo momento de reproducción de la canción.
     */
    virtual void seek(int64_t positionMs) = 0;

    virtual void onFinished(std::function<void()> callback) = 0;

    virtual void
    onStateChanged(std::function<void(PlaybackState)> callback) = 0;

    virtual void
    onDurationChanged(std::function<void(std::int64_t)> callback) = 0;

    virtual void
    onPositionChanged(std::function<void(std::int64_t)> callback) = 0;
};

} // namespace Track8::Player