#pragma once
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <string>

namespace Track8::Domain {

/**
 * @class Date
 * @brief Representa una fecha del estilo "YEAR-MONTH-DAY".
 */
class Date {
public:
    /**
     * Crea una fecha a partir de una string con formato YYYY-MM-DD.
     * @param date Fecha con formato YYYY-MM-DD.
     */
    explicit Date(const std::string& date) {
        std::istringstream ss{date};
        std::chrono::year_month_day ymd;
        std::chrono::from_stream(ss, "%F", ymd);

        if (ss.fail() || !ymd.ok())
            throw std::invalid_argument("Invalid date format.");

        m_year = static_cast<int>(ymd.year());
        m_month = static_cast<int>(static_cast<unsigned>(ymd.month()));
        m_day = static_cast<int>(static_cast<unsigned>(ymd.day()));
    }

    /**
     * Crea una fecha a partir del año, mes y día.
     * @param year El año de la fecha.
     * @param month El mes de la fecha.
     * @param day El día de la fecha.
     */
    Date(const int year, const int month, const int day) {
        m_year = year;
        m_month = month;
        m_day = day;
    }

    [[nodiscard]] int year() const { return m_year; }
    [[nodiscard]] int month() const { return m_month; }
    [[nodiscard]] int day() const { return m_day; }

private:
    int m_year = 0;
    int m_month = 0;
    int m_day = 0;
};

} // namespace Track8::Domain