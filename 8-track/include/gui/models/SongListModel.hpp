#pragma once

#include "domain/Song.hpp"

#include <QAbstractListModel>
#include <memory>
#include <vector>

namespace Track8::Gui {

/**
 * @class SongListModel
 * @brief Modelo de lista que expone canciones del dominio a la interfaz QML.
 */
class SongListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        SongIdRole = Qt::UserRole + 1,
        TitleRole,
        ArtistRole,
        AlbumRole,
        GenreRole,
        YearRole,
        PathRole
    };
    Q_ENUM(Role)

    explicit SongListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const { return static_cast<int>(m_songs.size()); }

    void setSongs(std::vector<std::shared_ptr<Domain::Song>> songs);
    void clear();

    const Domain::Song* songAt(int row) const;
    int indexOf(int songId) const;

signals:
    void countChanged();

private:
    std::vector<std::shared_ptr<Domain::Song>> m_songs;
};

} // namespace Track8::Gui