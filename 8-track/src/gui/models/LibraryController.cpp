#include "gui/models/LibraryController.hpp"

#include <QUrl>

namespace Track8::Gui {

namespace {
Domain::Date toDate(const QString& value) {
    const auto text = value.trimmed().toStdString();
    if (text.empty())
        return Domain::Date("0000-00-00");
    return Domain::Date(text);
}
} // namespace

LibraryController::LibraryController(Services::LibraryService& library,
                                     Services::SearchService& search,
                                     Services::ArtistService& artists,
                                     QObject* parent)
    : QObject(parent),
      m_stats(library.stats()),
      m_library(library),
      m_search(search),
      m_artists(artists) {}

void LibraryController::loadSongs() {
    m_songsModel.setSongs(m_library.songs());
}

void LibraryController::loadAlbums() {
    auto albums = m_library.albums();
    std::erase_if(albums, [](const std::shared_ptr<Domain::Album>& album) {
        return album->id() == 0;
    });

    m_albumsModel.setAlbums(std::move(albums));
}

void LibraryController::loadPerformers() {
    m_performersModel.setPerformers(m_artists.performers());
}

void LibraryController::refresh() {
    m_stats = m_library.stats();
    emit statsChanged();
}

void LibraryController::search(const QString& query) {
    const auto result = m_search.search(query.toStdString());

    if (result.success) {
        m_searchModel.setSongs(result.songs);
        m_searchError.clear();
    } else {
        m_searchModel.clear();
        m_searchError = QString::fromStdString(result.errorMessage);
    }

    emit searchErrorChanged();
}

void LibraryController::clearSearch() {
    m_searchModel.clear();
    m_searchError.clear();
    emit searchErrorChanged();
}

QString LibraryController::albumCover(const QString& path,
                                      const QString& name) const {
    const auto cover =
        m_library.albumCover(path.toStdString(), name.toStdString());

    if (!std::filesystem::exists(cover))
        return {};

    return QUrl::fromLocalFile(QString::fromStdString(cover.string()))
        .toString();
}

QString LibraryController::performerCover(const QString& name) const {
    const auto cover = m_library.performerCover(name.toStdString());

    if (!std::filesystem::exists(cover))
        return {};

    return QUrl::fromLocalFile(QString::fromStdString(cover.string()))
        .toString();
}

QVariantMap LibraryController::performerDetails(const int id) const {
    const auto performer = m_artists.find(id);
    if (!performer)
        return {};

    QVariantMap data{
        {"id", performer->id()},
        {"name", QString::fromStdString(performer->name())},
        {"type", static_cast<int>(performer->type())},
    };

    if (const auto artist =
            std::dynamic_pointer_cast<Domain::Artist>(performer)) {
        data["realName"] = QString::fromStdString(artist->real_name());
        data["birthDate"] =
            QString::fromStdString(artist->birth_date().asString());
        data["deathDate"] =
            artist->death_date()
                ? QString::fromStdString(artist->death_date()->asString())
                : QString{};
    } else if (const auto group =
                   std::dynamic_pointer_cast<Domain::Group>(performer)) {
        data["startDate"] =
            QString::fromStdString(group->start_date().asString());
        data["endDate"] =
            group->end_date()
                ? QString::fromStdString(group->end_date()->asString())
                : QString{};
    }

    return data;
}

bool LibraryController::savePerformer(
    const int id, const QString& name, const int selectedType,
    const QString& realName, const QString& birthDate, const QString& deathDate,
    const QString& startDate, const QString& endDate) {
    try {
        const auto original = m_artists.find(id);
        if (!original)
            return false;

        const auto newType = static_cast<Domain::PerformerType>(selectedType);
        const auto stdName = name.trimmed().toStdString();

        m_artists.updatePerformer(Domain::Performer(id, stdName, newType));

        if (newType != original->type()) {
            switch (newType) {
            case Domain::PerformerType::Person:
                m_artists.markAsPerson(id);
                break;
            case Domain::PerformerType::Group:
                m_artists.markAsGroup(id);
                break;
            default:
                m_artists.markAsUnknown(id);
                break;
            }
        }

        switch (newType) {
        case Domain::PerformerType::Person: {
            const Domain::Artist artist(id, stdName, realName.toStdString(),
                                        toDate(birthDate), toDate(deathDate));
            m_artists.updatePerson(artist);
            break;
        }
        case Domain::PerformerType::Group: {
            const Domain::Group group(id, stdName, toDate(startDate),
                                      toDate(endDate));
            m_artists.updateGroup(group);
            break;
        }
        default:
            break;
        }

        loadPerformers();
        refresh();
        return true;
    } catch (const std::exception& e) {
        qWarning() << "savePerformer:" << e.what();
        return false;
    }
}

} // namespace Track8::Gui