#include "gui/models/AlbumListModel.hpp"

namespace Track8::Gui {

AlbumListModel::AlbumListModel(QObject* parent) : QAbstractListModel(parent) {}

int AlbumListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;
    return count();
}

QVariant AlbumListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= count())
        return {};

    const auto& album = m_albums[index.row()];

    switch (role) {
    case AlbumIdRole:
        return album->id();
    case NameRole:
        return QString::fromStdString(album->name());
    case YearRole:
        return album->year();
    case PathRole:
        return QString::fromStdString(album->path());
    default:
        return {};
    }
}

const Domain::Album* AlbumListModel::albumAt(int row) const {
    if (row < 0 || row >= count())
        return nullptr;
    return m_albums[row].get();
}

int AlbumListModel::indexOf(int albumId) const {
    for (int row = 0; row < count(); ++row) {
        if (m_albums[row]->id() == albumId)
            return row;
    }
    return -1;
}

void AlbumListModel::setAlbums(
    std::vector<std::shared_ptr<Domain::Album>> albums) {
    beginResetModel();
    m_albums = std::move(albums);
    endResetModel();
    emit countChanged();
}

QHash<int, QByteArray> AlbumListModel::roleNames() const {
    return {{AlbumIdRole, "albumId"},
            {NameRole, "name"},
            {YearRole, "year"},
            {PathRole, "path"}};
}

void AlbumListModel::clear() {
    setAlbums({});
}
} // namespace Track8::Gui