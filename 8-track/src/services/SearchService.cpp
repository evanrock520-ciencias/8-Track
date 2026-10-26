#include "services/SearchService.hpp"
#include "compiler/QueryCompiler.hpp"
#include "services/SearchResult.hpp"

namespace Track8::Services {

SearchResult SearchService::search(const std::string& source) const {
    try {
        const auto query = Compiler::QueryCompiler::compile(source);
        const auto songs = m_songs->find(query);
        return {.success = true, .songs = songs, .errorMessage = ""};
    } catch (const std::exception& exception) {
        return {
            .success = false, .songs = {}, .errorMessage = exception.what()};
    }
}

} // namespace Track8::Services