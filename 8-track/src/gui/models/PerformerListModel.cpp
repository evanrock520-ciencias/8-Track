#include "gui/models/PerformerListModel.hpp"

namespace Track8::Gui {

PerformerListModel::PerformerListModel(QObject* parent)
    : QAbstractListModel(parent) {}

int PerformerListModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid())
        return 0;
    return count();
}

QVariant PerformerListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= count())
        return {};

    const auto& performer = m_performers[index.row()];

    switch (role) {
    case PerformerIdRole:
        return performer->id();
    case NameRole:
        return QString::fromStdString(performer->name());
    default:
        return {};
    }
}

const Domain::Performer* PerformerListModel::performerAt(int row) const {
    if (row < 0 || row >= count())
        return nullptr;
    return m_performers[row].get();
}

int PerformerListModel::indexOf(int albumId) const {
    for (int row = 0; row < count(); ++row) {
        if (m_performers[row]->id() == albumId)
            return row;
    }
    return -1;
}

void PerformerListModel::setPerformers(
    std::vector<std::shared_ptr<Domain::Performer>> performers) {
    beginResetModel();
    m_performers = std::move(performers);
    endResetModel();
    emit countChanged();
}

QHash<int, QByteArray> PerformerListModel::roleNames() const {
    return {{PerformerIdRole, "performerId"}, {NameRole, "name"}};
}

void PerformerListModel::clear() {
    setPerformers({});
}

} // namespace Track8::Gui