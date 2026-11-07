#pragma once
#include "domain/Song.hpp"

#include <deque>
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
    void addSong(Domain::Song song);

    /**
     * Elimina un canción de la cola.
     * @param song La canción a eliminar.
     */
    void removeSong(Domain::Song song);

    /**
     * Añade una canción al inicio de la cola.
     * @param song La canción a agregar.
     */
    void playNext(Domain::Song song);

    /**
     * Mezcla las canciones en la cola.
     */
    void shuffle();

private:
    std::deque<Domain::Song> m_queue{};
    std::stack<Domain::Song> m_history{};
};

} // namespace Track8::Player