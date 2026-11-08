#pragma once
#include "domain/Song.hpp"

#include <deque>
#include <optional>
#include <random>
#include <stack>
#include <vector>

namespace Track8::Player {

/**
 * Mantiene el estado de reproducción y el historial.
 */
class Queue {
public:
    explicit Queue(const std::vector<Domain::Song>& songs);

    /**
     * Regresa la canción actual.
     * @return La canción actual, o std::nullopt si no hay ninguna.
     */
    [[nodiscard]] std::optional<Domain::Song> current() const;

    /**
     * Mueve el índice a la siguiente canción.
     */
    void next();

    /**
     * Mueve el índice a la canción anterior.
     */
    void previous();

    /**
     * Añade una canción al final de la cola.
     * @param song La canción a agregar.
     */
    void addSong(const Domain::Song& song);

    /**
     * Añade una canción a la cola del usuario.
     * @param song La canción a agregar.
     */
    void userAddSong(const Domain::Song& song);

    /**
     * Elimina un canción de la cola.
     * @param song La canción a eliminar.
     */
    void remove(const Domain::Song& song);

    /**
     * Añade una canción al inicio de la cola.
     * @param song La canción a agregar.
     */
    void playNext(const Domain::Song& song);

    /**
     * Mezcla las canciones en la cola.
     */
    void shuffle();

    /**
     * Regresa la cola de reproducción a su estado original.
     */
    void disableShuffle();

    /**
     * Regresa el total de canciones en la cola y la cola del usuario.
     * @return El total de canciones en la cola y la cola del usuario.
     */
    [[nodiscard]] std::size_t size() const;

    /**
     * Regresa todas las canciones en la cola.
     * @return Todas las canciones en la cola.
     */
    [[nodiscard]] std::vector<Domain::Song> songsInQueue();

    /**
     * Regresa todas las canciones en el historial.
     * @return Todas las canciones en el historial.
     */
    [[nodiscard]] std::vector<Domain::Song> songsInHistory() const;

private:
    std::optional<Domain::Song> m_current;
    std::deque<Domain::Song> m_queue{};
    std::deque<Domain::Song> m_original{};
    std::deque<Domain::Song> m_userQueue{};
    std::stack<Domain::Song> m_history{};
    std::mt19937 m_rng{std::random_device{}()};
};

} // namespace Track8::Player
