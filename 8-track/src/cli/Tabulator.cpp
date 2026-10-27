#include "cli/Tabulator.hpp"

#include "domain/Song.hpp"

#include <iostream>
#include <tabulate/color.hpp>
#include <tabulate/font_align.hpp>
#include <tabulate/font_style.hpp>
#include <tabulate/table.hpp>

namespace Track8::Cli {

tabulate::Table
Tabulator::tabulate(const std::vector<std::shared_ptr<Domain::Song>>& songs) {
    using namespace tabulate;
    Table songsTable;
    songsTable.use_unicode_borders(true, BorderStyle::Heavy);
    songsTable.format().multi_byte_characters(true);

    songsTable.add_row({"Title", "Performer", "Album", "Release Year"});
    for (const auto& song : songs)
        songsTable.add_row({song->title(), song->performer()->name(),
                            song->album()->name(),
                            std::to_string(song->year())});

    songsTable.column(0).format().font_style({FontStyle::bold});
    songsTable.column(2).format().font_align(FontAlign::center);
    songsTable.column(3).format().font_align(FontAlign::right);

    for (size_t i = 0; i < 4; ++i) {
        songsTable[0][i]
            .format()
            .font_color(Color::red)
            .font_align(FontAlign::center)
            .font_style({FontStyle::bold});
    }

    return songsTable;
}

[[nodiscard]] tabulate::Table Tabulator::tabulate(
    const std::vector<std::shared_ptr<Domain::Performer>>& performers) {
    using namespace tabulate;
    Table songsTable;
    songsTable.use_unicode_borders(true, BorderStyle::Heavy);
    songsTable.format().multi_byte_characters(true);

    songsTable.add_row({"Id", "Name"});
    for (const auto& performer : performers)
        songsTable.add_row(
            {std::to_string(performer->id()), performer->name()});

    songsTable.column(0).format().font_style({FontStyle::bold});
    songsTable.column(1).format().font_align(FontAlign::center);

    for (size_t i = 0; i < 2; ++i) {
        songsTable[0][i]
            .format()
            .font_color(Color::red)
            .font_align(FontAlign::center)
            .font_style({FontStyle::bold});
    }

    return songsTable;
}

} // namespace Track8::Cli