#pragma once

#include "domain/Album.hpp"

#include <QAbstractListModel>
#include <memory>
#include <vector>

namespace Track8::Gui {

/**
 * @class AlbumListModel
 * @brief Modelo de lista que expone álbums del dominio a la interfaz QML.
 */
class AlbumListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        AlbumIdRole = Qt::UserRole + 1,
        NameRole,
        YearRole,
        PathRole,
    };
    Q_ENUM(Role)

    explicit AlbumListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const { return static_cast<int>(m_albums.size()); }

    void setAlbums(std::vector<std::shared_ptr<Domain::Album>> albums);
    void clear();

    const Domain::Album* albumAt(int row) const;
    int indexOf(int albumId) const;

signals:
    void countChanged();

private:
    std::vector<std::shared_ptr<Domain::Album>> m_albums;
};

} // namespace Track8::Gui