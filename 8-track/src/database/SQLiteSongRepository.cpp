#include "database/SQLiteSongRepository.hpp"

namespace Track8::Database {

SQLiteSongRepository::SQLiteSongRepository(const QSqlDatabase& database)
    : m_database(database) {}

} // namespace Track8::Database