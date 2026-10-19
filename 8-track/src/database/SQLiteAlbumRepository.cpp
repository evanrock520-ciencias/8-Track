#include "database/SQLiteAlbumRepository.hpp"

#include <QSqlError>
#include <QSqlQuery>
#include <stdexcept>

namespace Track8::Database {

SQLiteAlbumRepository::SQLiteAlbumRepository(const QSqlDatabase& database)
    : m_database(database) {}

int SQLiteAlbumRepository::save(const Domain::Album& album) {
    QSqlQuery query(m_database);
    query.prepare(
        "INSERT INTO albums (path, name, year) VALUES (:path, :name, :year)");
    query.bindValue(":path", QString::fromStdString(album.path()));
    query.bindValue(":name", QString::fromStdString(album.name()));
    query.bindValue(":year",
                    QString::fromStdString(std::to_string(album.year())));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    return query.lastInsertId().toInt();
}

std::shared_ptr<Domain::Album> SQLiteAlbumRepository::find(const int id) {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM albums WHERE id_album = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    const auto path = query.value("path").toString();
    const auto name = query.value("name").toString();
    auto year = query.value("year").toInt();

    return std::make_shared<Domain::Album>(id, path.toStdString(),
                                           name.toStdString(), year);
}

std::shared_ptr<Domain::Album>
SQLiteAlbumRepository::find(const std::string& name,
                            const std::filesystem::path& path) {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM albums WHERE name = :name AND path = :path");
    query.bindValue(":name", name.c_str());
    query.bindValue(":path", path.string().c_str());

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    auto id = query.value("id_album").toInt();
    auto year = query.value("year").toInt();

    return std::make_shared<Domain::Album>(id, path.string(), name, year);
}

void SQLiteAlbumRepository::update(const Domain::Album& album) {
    QSqlQuery query(m_database);
    query.prepare("UPDATE albums SET path = :path, name = :name, year = :year "
                  "WHERE id_album = :id");
    query.bindValue(":path", QString::fromStdString(album.path()));
    query.bindValue(":name", QString::fromStdString(album.name()));
    query.bindValue(":year", album.year());
    query.bindValue(":id", album.id());

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

std::vector<std::shared_ptr<Domain::Album>> SQLiteAlbumRepository::getAll() {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM albums");

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    std::vector<std::shared_ptr<Domain::Album>> albums;
    while (query.next()) {
        albums.push_back(std::make_shared<Domain::Album>(
            query.value("id_album").toInt(),
            query.value("path").toString().toStdString(),
            query.value("name").toString().toStdString(),
            query.value("year").toInt()));
    }

    return albums;
}

unsigned int SQLiteAlbumRepository::count() {
    return getAll().size();
}

} // namespace Track8::Database