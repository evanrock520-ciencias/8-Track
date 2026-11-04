#pragma once

#include "domain/Performer.hpp"

#include <QAbstractListModel>
#include <memory>
#include <vector>

namespace Track8::Gui {

/**
 * @class PerformerListModel
 * @brief Modelo de lista que expone intérpretes del dominio a la interfaz QML.
 */
class PerformerListModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        PerformerIdRole = Qt::UserRole + 1,
        NameRole,
    };
    Q_ENUM(Role)

    explicit PerformerListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    int count() const { return static_cast<int>(m_performers.size()); }

    void
    setPerformers(std::vector<std::shared_ptr<Domain::Performer>> performers);
    void clear();

    const Domain::Performer* performerAt(int row) const;
    int indexOf(int performerId) const;

signals:
    void countChanged();

private:
    std::vector<std::shared_ptr<Domain::Performer>> m_performers;
};

} // namespace Track8::Gui