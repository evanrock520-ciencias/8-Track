#include "cli/Cli.hpp"

#include "cli/Tabulator.hpp"
#include "services/LibraryService.hpp"
#include "services/SearchService.hpp"

#include <argparse/argparse.hpp>

namespace Track8::Cli {

Cli::Cli(Services::LibraryService& library, Services::SearchService& search)
    : m_library(library), m_search(search) {}

void Cli::run(const int argc, char** argv) const {
    argparse::ArgumentParser program("8-track");

    program.add_argument("--scan", "-s")
        .help("scan a directory for MP3 files.");
    program.add_argument("--query", "-q")
        .help("search the music metadata database.");
    program.add_argument("--list", "-l")
        .default_value(false)
        .implicit_value(true)
        .help("list the complete rolas table.");

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        throw std::runtime_error(err.what());
    }

    // Si se solicita escanear un directorio.
    if (program.is_used("--scan")) {
        const auto path = program.get<std::string>("--scan");
        std::cout << "Scanning " << path << std::endl;
        m_library.scan(path);
    }

    if (program.is_used("--list"))
        list();

    // Si se solicita realizar una consulta por consola.
    if (program.is_used("--query")) {
        const auto query = program.get<std::string>("--query");
        queryTable(query);
    }
}

void Cli::list() const {
    const auto songs = m_library.songs();
    const auto table = Tabulator::tabulate(songs);
    std::cout << table << std::endl;
}

void Cli::queryTable(const std::string& rawQuery) const {
    const auto result = m_search.search(rawQuery);
    if (!result.success)
        std::cerr << result.errorMessage << std::endl;

    const auto table = Tabulator::tabulate(result.songs);
    std::cout << table << std::endl;
}

} // namespace Track8::Cli