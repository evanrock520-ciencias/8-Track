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
        if (date.size() < 10)
            throw std::invalid_argument("Date is too short.");
        if (date[4] != '-' || date[7] != '-')
            throw std::invalid_argument("Invalid date format.");

        try {
            m_year = std::stoi(date.substr(0, 4));
            m_month = std::stoi(date.substr(5, 2));
            m_day = std::stoi(date.substr(8, 2));
        } catch (const std::exception& e) {
            throw std::invalid_argument(e.what());
        }

        if (m_year < 0 || m_year > 9999)
            throw std::invalid_argument("Invalid year.");
        if (m_month < 0 || m_month > 12)
            throw std::invalid_argument("Invalid month.");
        if (m_day < 0 || m_day > 31)
            throw std::invalid_argument("Invalid day.");
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