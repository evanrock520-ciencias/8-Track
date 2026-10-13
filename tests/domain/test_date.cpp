#include "../../8-track/include/domain/Album.hpp"
#include "../../8-track/include/domain/Date.hpp"

#include <gtest/gtest.h>

using namespace Track8::Domain;

TEST(Date, MatchWithStringDate) {
    const Date date("2000-12-20");
    ASSERT_EQ(date.year(), 2000);
    ASSERT_EQ(date.month(), 12);
    ASSERT_EQ(date.day(), 20);
}

TEST(Date, MatchWithYearMonthDayDate) {
    const Date date(1989, 2, 24); // “Diane, 11:30 a.m., February 24th. Entering
                                  // the town of Twin Peaks.”
    ASSERT_EQ(date.year(), 1989);
    ASSERT_EQ(date.month(), 2);
    ASSERT_EQ(date.day(), 24);
}

TEST(Date, InvalidDate) {
    ASSERT_ANY_THROW(Date("invalid"));    // Sin formato
    ASSERT_ANY_THROW(Date("abcd-12-12")); // Año inválido por usar letras.
    ASSERT_ANY_THROW(
        Date("1990-ab-cd")); // Mes y día inválidos por usar letras.
    ASSERT_ANY_THROW(Date("1999-13-20"));  // Mes inválido.
    ASSERT_ANY_THROW(Date("1999-10-56"));  // Día inválido.
    ASSERT_ANY_THROW(Date("20478-10-56")); // Año inválido.

    // Aún me podrian poner un fecha inexistente y funcionaría.
    // TODO: Reforzar módulo de fecha. (Si hay tiempo)
    // Date date("2026-02-31");
}
