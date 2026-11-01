#include "gui/models/SongListModel.hpp"

namespace Track8::Gui {

SongListModel::SongListModel(QObject* parent) : QAbstractListModel(parent) {}

int SongListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;
    return count();
}

QVariant SongListModel::data(const QModelIndex& index, const int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= count())
        return {};

    const auto& song = m_songs[index.row()];

    switch (role) {
    case SongIdRole:
        return song->id();
    case TitleRole:
        return QString::fromStdString(song->title());
    case ArtistRole:
        return song->performer()
                   ? QString::fromStdString(song->performer()->name())
                   : QString();
    case AlbumRole:
        return song->album() ? QString::fromStdString(song->album()->name())
                             : QString();
    case GenreRole:
        return QString::fromStdString(song->genre());
    case YearRole:
        return song->year();
    default:
        return {};
    }
}

QHash<int, QByteArray> SongListModel::roleNames() const {
    return {{SongIdRole, "songId"}, {TitleRole, "title"},
            {ArtistRole, "artist"}, {AlbumRole, "album"},
            {GenreRole, "genre"},   {YearRole, "year"}};
}

void SongListModel::setSongs(std::vector<std::shared_ptr<Domain::Song>> songs) {
    beginResetModel();
    m_songs = std::move(songs);
    endResetModel();
    emit countChanged();
}

void SongListModel::clear() {
    setSongs({});
}

const Domain::Song* SongListModel::songAt(const int row) const {
    if (row < 0 || row >= count())
        return nullptr;
    return m_songs[row].get();
}

int SongListModel::indexOf(const int songId) const {
    for (int row = 0; row < count(); ++row) {
        if (m_songs[row]->id() == songId)
            return row;
    }
    return -1;
}

} // namespace Track8::Gui