#include "database/SQLitePerformerRepository.hpp"

#include <QSqlError>
#include <QSqlQuery>
#include <stdexcept>

namespace Track8::Database {

SQLitePerformerRepository::SQLitePerformerRepository(
    const QSqlDatabase& database)
    : m_database(database) {}

int SQLitePerformerRepository::save(const std::string& name) {
    QSqlQuery query(m_database);
    query.prepare(
        "INSERT INTO performers (id_type, name) VALUES (:id_type, :name)");
    query.bindValue(":id_type", 2); // En un inicio siempre es 'Unknown'
    query.bindValue(":name", QString::fromStdString(name));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    return query.lastInsertId().toInt();
}

std::shared_ptr<Domain::Performer>
SQLitePerformerRepository::find(const std::string& name) {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM performers WHERE name = :name");
    query.bindValue(":name", QString::fromStdString(name));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    const auto id = query.value("id_performer").toInt();

    return std::make_shared<Domain::Performer>(id, name);
}

std::shared_ptr<Domain::Performer> SQLitePerformerRepository::find(int id) {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM performers WHERE id_performer = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    const auto name = query.value("name").toString().toStdString();

    switch (query.value("id_type").toInt()) {
    case 0:
        return findArtist(id);
    case 1:
        return findGroup(id);
    case 2:
        return std::make_shared<Domain::Performer>(id, name);
    default:
        return nullptr;
    }
}

void SQLitePerformerRepository::markAsArtist(int id) {
    if (!m_database.transaction())
        throw std::runtime_error(m_database.lastError().text().toStdString());

    QSqlQuery update(m_database);
    update.prepare(
        "UPDATE performers SET id_type = :id_type WHERE id_performer = :id");
    update.bindValue(":id_type", 0); // 0 = persons
    update.bindValue(":id", id);

    if (!update.exec()) {
        m_database.rollback();
        throw std::runtime_error(update.lastError().text().toStdString());
    }

    const auto name = findName(id);
    if (!name) {
        m_database.rollback();
        throw std::runtime_error("Performer with id " + std::to_string(id) +
                                 " not found");
    }

    QSqlQuery insert(m_database);
    insert.prepare("INSERT OR IGNORE INTO persons (id_person, stage_name, "
                   "real_name, birth_date, death_date) VALUES (:id, "
                   ":stage_name, :real_name, :birth_date, :death_date)");
    insert.bindValue(":id", id);
    insert.bindValue(":stage_name", QString::fromStdString(*name));
    insert.bindValue(":real_name", "Unknown");
    insert.bindValue(":birth_date", "0000-00-00");
    insert.bindValue(":death_date", "0000-00-00");

    if (!insert.exec()) {
        m_database.rollback();
        throw std::runtime_error(insert.lastError().text().toStdString());
    }

    QSqlQuery removeMembers(m_database);
    removeMembers.prepare("DELETE FROM in_group WHERE id_group = :id");
    removeMembers.bindValue(":id", id);

    if (!removeMembers.exec()) {
        m_database.rollback();
        throw std::runtime_error(
            removeMembers.lastError().text().toStdString());
    }

    QSqlQuery removeGroup(m_database);
    removeGroup.prepare("DELETE FROM groups WHERE id_group = :id");
    removeGroup.bindValue(":id", id);

    if (!removeGroup.exec()) {
        m_database.rollback();
        throw std::runtime_error(removeGroup.lastError().text().toStdString());
    }

    if (!m_database.commit())
        throw std::runtime_error(m_database.lastError().text().toStdString());
}

void SQLitePerformerRepository::markAsGroup(int id) {
    if (!m_database.transaction())
        throw std::runtime_error(m_database.lastError().text().toStdString());

    QSqlQuery update(m_database);
    update.prepare(
        "UPDATE performers SET id_type = :id_type WHERE id_performer = :id");
    update.bindValue(":id_type", 1); // 1 = groups
    update.bindValue(":id", id);

    if (!update.exec()) {
        m_database.rollback();
        throw std::runtime_error(update.lastError().text().toStdString());
    }

    const auto name = findName(id);
    if (!name) {
        m_database.rollback();
        throw std::runtime_error("Performer with id " + std::to_string(id) +
                                 " not found");
    }

    QSqlQuery insert(m_database);
    insert.prepare("INSERT OR IGNORE INTO groups (id_group, name, start_date, "
                   "end_date) VALUES (:id, :name, :start_date, :end_date)");
    insert.bindValue(":id", id);
    insert.bindValue(":name", QString::fromStdString(*name));
    insert.bindValue(":start_date", "0000-00-00");
    insert.bindValue(":end_date", "0000-00-00");

    if (!insert.exec()) {
        m_database.rollback();
        throw std::runtime_error(insert.lastError().text().toStdString());
    }

    QSqlQuery remove(m_database);
    remove.prepare("DELETE FROM persons WHERE id_person = :id");
    remove.bindValue(":id", id);

    if (!remove.exec()) {
        m_database.rollback();
        throw std::runtime_error(remove.lastError().text().toStdString());
    }

    if (!m_database.commit())
        throw std::runtime_error(m_database.lastError().text().toStdString());
}

void SQLitePerformerRepository::addToGroup(int groupId, int performerId) {
    QSqlQuery query(m_database);
    query.prepare("INSERT OR IGNORE INTO in_group (id_person, id_group) VALUES "
                  "(:id_person, :id_group)");
    query.bindValue(":id_person", performerId);
    query.bindValue(":id_group", groupId);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

void SQLitePerformerRepository::removeFromGroup(int groupId, int performerId) {
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM in_group WHERE id_person = :id_person AND "
                  "id_group = :id_group");
    query.bindValue(":id_person", performerId);
    query.bindValue(":id_group", groupId);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

std::vector<std::shared_ptr<Domain::Artist>>
SQLitePerformerRepository::getMembers(int groupId) {
    QSqlQuery query(m_database);
    query.prepare(
        "SELECT person.id_person, person.stage_name, person.real_name, "
        "person.birth_date, person.death_date FROM in_group ig JOIN persons "
        "person ON person.id_person = ig.id_person WHERE ig.id_group = :id");
    query.bindValue(":id", groupId);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    std::vector<std::shared_ptr<Domain::Artist>> members;
    while (query.next()) {
        const auto id = query.value("id_person").toInt();
        members.push_back(std::make_shared<Domain::Artist>(
            id, query.value("stage_name").toString().toStdString(),
            query.value("real_name").toString().toStdString(),
            Domain::Date(query.value("birth_date").toString().toStdString()),
            Domain::Date(query.value("death_date").toString().toStdString())));
    }
    return members;
}

void SQLitePerformerRepository::update(const Domain::Performer& performer) {
    QSqlQuery query(m_database);
    query.prepare(
        "UPDATE performers SET name = :name WHERE id_performer = :id");
    query.bindValue(":name", QString::fromStdString(performer.name()));
    query.bindValue(":id", performer.id());

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

void SQLitePerformerRepository::update(const Domain::Artist& artist) {
    QSqlQuery query(m_database);
    query.prepare("UPDATE persons SET stage_name = :stage_name, real_name = "
                  ":real_name, birth_date = :birth_date, death_date = "
                  ":death_date WHERE id_person = :id_person");
    query.bindValue(":stage_name", QString::fromStdString(artist.stage_name()));
    query.bindValue(":real_name", QString::fromStdString(artist.real_name()));
    query.bindValue(":birth_date",
                    QString::fromStdString(artist.birth_date().asString()));
    query.bindValue(":id", artist.id());

    std::string death_date = "0000-00-00";
    if (artist.death_date())
        death_date = artist.death_date()->asString();
    query.bindValue(":death_date", QString::fromStdString(death_date));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

void SQLitePerformerRepository::update(const Domain::Group& group) {
    QSqlQuery query(m_database);
    query.prepare("UPDATE groups SET name = :name, start_date = :start_date, "
                  "end_date = :end_date WHERE id_group = :id");
    query.bindValue(":name", QString::fromStdString(group.name()));
    query.bindValue(":start_date",
                    QString::fromStdString(group.start_date().asString()));
    query.bindValue(":id", group.id());

    std::string end_date = "0000-00-00";
    if (group.end_date())
        end_date = group.end_date()->asString();
    query.bindValue(":end_date", QString::fromStdString(end_date));

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());
}

std::vector<std::shared_ptr<Domain::Performer>>
SQLitePerformerRepository::getAll() {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM performers");

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    std::vector<std::shared_ptr<Domain::Performer>> performers;
    while (query.next()) {
        performers.emplace_back(std::make_shared<Domain::Performer>(
            query.value("id_performer").toInt(),
            query.value("name").toString().toStdString()));
    }

    return performers;
}

std::shared_ptr<Domain::Artist>
SQLitePerformerRepository::findArtist(int id) const {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM persons WHERE id_person = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    const auto stage_name = query.value("stage_name").toString().toStdString();
    const auto real_name = query.value("real_name").toString().toStdString();
    const auto birth_date = query.value("birth_date").toString().toStdString();
    const auto death_date = query.value("death_date").toString().toStdString();

    return std::make_shared<Domain::Artist>(id, stage_name, real_name,
                                            Domain::Date(birth_date),
                                            Domain::Date(death_date));
}

std::shared_ptr<Domain::Group>
SQLitePerformerRepository::findGroup(int id) const {
    QSqlQuery query(m_database);
    query.prepare("SELECT * FROM groups WHERE id_group = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return nullptr;

    const auto name = query.value("name").toString().toStdString();
    const auto start_date = query.value("start_date").toString().toStdString();
    const auto end_date = query.value("end_date").toString().toStdString();

    return std::make_shared<Domain::Group>(id, name, Domain::Date(start_date),
                                           Domain::Date(end_date));
}

std::optional<std::string>
SQLitePerformerRepository::findName(const int id) const {
    QSqlQuery query(m_database);
    query.prepare("SELECT name FROM performers WHERE id_performer = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        throw std::runtime_error(query.lastError().text().toStdString());

    if (!query.next())
        return std::nullopt;

    return query.value("name").toString().toStdString();
}

} // namespace Track8::Database