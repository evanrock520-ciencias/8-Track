#include "gui/models/LibraryController.hpp"

namespace Track8::Gui {

LibraryController::LibraryController(Services::LibraryService& library,
                                     Services::ArtistService& artists,
                                     QObject* parent)
    : QObject(parent),
      m_stats(library.stats()),
      m_library(library),
      m_artists(artists) {}

void LibraryController::refresh() {
    m_stats = m_library.stats();
    emit statsChanged();
}

} // namespace Track8::Gui