#include "miner/Miner.hpp"

#include <argparse/argparse.hpp>
#include <iostream>
#include <string>

// En realidad deberia llamar a la capa de servicios.
static void scan(std::string directory) {
    using namespace Track8::Miner;
    const Miner miner(std::move(directory));
    miner.mine([](const Track8::Miner::Metadata& metadata) {
        std::cout << metadata.m_path << '\n';
    });
}

int main(int argc, char* argv[]) {
    argparse::ArgumentParser program("8-track");

    program.add_argument("--scan", "-s")
        .help("scan a directory for MP3 files.");
    program.add_argument("--query", "-q")
        .help("search the music metadata database.");
    program.add_argument("--database", "-d")
        .help("path to the music metadata database.");

    try {
        program.parse_args(argc, argv);
    } catch (const std::exception& err) {
        std::cerr << err.what() << '\n';
        std::cerr << program;
        return 1;
    }

    // Si se solicita escanear un directorio.
    if (program.is_used("--scan")) {
        const auto path = program.get<std::string>("--scan");
        std::cout << "Scanning " << path << '\n';
        // TODO: Minar un directorio.
        scan(path);
    }

    // Si se solicita realizar una consulta por consola.
    if (program.is_used("--query")) {
        if (!program.is_used("--database")) {
            std::cerr << "query requires to specify database\n";
            return 1;
        }

        const auto query = program.get<std::string>("--query");
        const auto database = program.get<std::string>("--database");

        std::cout << "Querying " << query << " from " << database << '\n';
        // TODO: Tabular la consulta
    }

    // TODO: Lanzar la aplicación gráfica.

    return 0;
}