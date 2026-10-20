#include "cli/Cli.hpp"

#include "cli/Tabulator.hpp"

#include <argparse/argparse.hpp>

namespace Track8::Cli {

Cli::Cli(Services::LibraryService& library) : m_library(library) {}

void Cli::run(int argc, char** argv) {
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

        std::cout << "Querying " << query << '\n';
        // TODO: Tabular la consulta
    }
}

void Cli::list() const {
    const auto songs = m_library.songs();
    const auto table = Tabulator::tabulate(songs);
    std::cout << table << std::endl;
}

void Cli::query(const std::string& rawQuery) {}

} // namespace Track8::Cli