#include "database/SQLitePerformerRepository.hpp"

namespace Track8::Database {

SQLitePerformerRepository::SQLitePerformerRepository(
    const QSqlDatabase& database)
    : m_database(database) {}

} // namespace Track8::Database