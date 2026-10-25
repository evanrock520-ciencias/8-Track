#include "database/SQLiteSongRepository.hpp"

#include "compiler/SQLCompiler.hpp"
#include "compiler/transpiler/SQLTranspiler.hpp"

#include <QSqlError>
#include <QSqlQuery>
#include <stdexcept>
#include <utility>

namespace Track8::Database {

SQLiteSongRepository::SQLiteSongRepository(
    const QSqlDatabase& database,
    std::shared_ptr<IPerformerRepository> performers,
    std::shared_ptr<IAlbumRepository> albums)
    : m_database(database),
      m_albums(std::move(albums)),
      m_performers(std::move(performers)) {}

int SQLiteSongRepository::save(const Domain::Song& song) {
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO rolas (id_performer, id_album, path, title, "
                  "track, year, genre) VALUES (:id_performer, :id_album, "
                  ":path, :title, :track, :year, :genre)");
    query.bindValue(":id_performer", song.performer()->id());
    query.bindValue(":id_album", song.album()->id());
    query.bindValue(":path", QString::fromStdString(song.path()));
    query.bindValue(":title", QString::fromStdString(song.title()));
    query.bindValue(":track", song.track());
    query.bindValue(":year", song.year());
    query.bindValue(":genre", QString::fromStdString(song.genre()));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    return query.lastInsertId().toInt();
}

std::shared_ptr<Domain::Song> SQLiteSongRepository::find(int id) {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM rolas WHERE id_rola = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    return buildSong(query);
}

std::shared_ptr<Domain::Song>
SQLiteSongRepository::find(const std::filesystem::path& path) {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM rolas WHERE path = :path");
    query.bindValue(":path", QString::fromStdString(path.string()));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    return buildSong(query);
}

std::vector<std::shared_ptr<Domain::Song>>
SQLiteSongRepository::find(const Compiler::Query& query) {
    Compiler::SQL::SQLTranspiler transpiler;
    const auto sqlQuery = transpiler.generate(query);

    QSqlQuery queryDatabase(m_database);
    queryDatabase.prepare(QString::fromStdString(sqlQuery.generated));

    for (const auto& binding : sqlQuery.bindings) {
        if (std::holds_alternative<std::string>(binding)) {
            queryDatabase.addBindValue(
                QString::fromStdString(std::get<std::string>(binding)));
        } else {
            queryDatabase.addBindValue(std::get<int>(binding));
        }
    }

    if (!queryDatabase.exec())
        throw std::runtime_error(
            queryDatabase.lastError().text().toStdString());

    std::vector<std::shared_ptr<Domain::Song>> songs;
    while (queryDatabase.next())
        if (auto song = buildSong(queryDatabase))
            songs.push_back(std::move(song));

    return songs;

    return {};
}

void SQLiteSongRepository::remove(int id) {
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM rolas WHERE id_rola = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

void SQLiteSongRepository::update(const Domain::Song& song) {
    QSqlQuery query(m_database);
    query.prepare("UPDATE rolas SET id_performer = :id_performer, id_album = "
                  ":id_album, path = :path, title = :title, "
                  "track = :track, year = :year, genre = :genre WHERE id_rola "
                  "= :id_rola");
    query.bindValue(":id_performer", song.performer()->id());
    query.bindValue(":id_album", song.album()->id());
    query.bindValue(":path", QString::fromStdString(song.path()));
    query.bindValue(":title", QString::fromStdString(song.title()));
    query.bindValue(":track", song.track());
    query.bindValue(":year", song.year());
    query.bindValue(":genre", QString::fromStdString(song.genre()));
    query.bindValue(":id_rola", song.id());

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

std::vector<std::shared_ptr<Domain::Song>> SQLiteSongRepository::getAll() {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM rolas");

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    std::vector<std::shared_ptr<Domain::Song>> songs;
    while (query.next())
        if (auto song = buildSong(query))
            songs.push_back(std::move(song));

    return songs;
}

std::shared_ptr<Domain::Song>
SQLiteSongRepository::buildSong(const QSqlQuery& query) const {
    const auto performer =
        m_performers->find(query.value("id_performer").toInt());
    const auto album = m_albums->find(query.value("id_album").toInt());

    if (!performer || !album)
        return nullptr;

    auto song = Domain::SongBuilder()
                    .with_id(query.value("id_rola").toInt())
                    .with_title(query.value("title").toString().toStdString())
                    .with_genre(query.value("genre").toString().toStdString())
                    .with_path(query.value("path").toString().toStdString())
                    .with_year(query.value("year").toInt())
                    .with_track(query.value("track").toInt())
                    .with_album(album)
                    .with_performer(performer)
                    .create();

    return std::make_shared<Domain::Song>(std::move(song));
}

unsigned int SQLiteSongRepository::count() {
    return getAll().size();
}

} // namespace Track8::Database