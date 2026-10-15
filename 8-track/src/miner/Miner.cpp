#include "miner/Miner.hpp"
#include "miner/Metadata.hpp"
#include "utils/Utils.hpp"

#include <functional>
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>

#include <utility>

namespace Track8::Miner {

Miner::Miner(std::filesystem::path path) : m_path(std::move(path)) {};

void Miner::mine(const std::function<void(const Metadata&)>& callback) const {
    if (!std::filesystem::exists(m_path)) {
        throw std::runtime_error("Invalid directory");
    }

    for (const auto& entry :
         std::filesystem::recursive_directory_iterator(m_path)) {
        if (entry.is_regular_file()) {
            if (entry.path().extension() != ".mp3")
                continue;

            try {
                Metadata metadata = parseFile(entry.path());
                callback(metadata);
            } catch (const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}

Metadata Miner::parseFile(const std::filesystem::path& path) {
    Metadata metadata;
    metadata.m_path = path;

    const TagLib::FileRef fileRef(path.c_str());
    if (fileRef.isNull())
        throw std::runtime_error("Could not open file.");
    if (!fileRef.tag())
        throw std::runtime_error("Could not read file.");

    const TagLib::Tag* tag = fileRef.tag();

    if (!Utils::empty(tag->title().to8Bit()))
        metadata.m_title = tag->title().to8Bit(true);

    if (!Utils::empty(tag->artist().to8Bit()))
        metadata.m_performer = tag->artist().to8Bit(true);

    if (!Utils::empty(tag->album().to8Bit()))
        metadata.m_album = tag->album().to8Bit(true);

    if (!Utils::empty(tag->album().to8Bit()))
        metadata.m_genre = tag->genre().to8Bit(true);

    metadata.m_year =
        (tag->year() > 0) ? tag->year() : 2026; // Si no tiene, será 2026.
    metadata.m_trackNumber =
        (tag->track() > 0) ? tag->track() : 1; // Si no tiene, será 1.

    return metadata;
}

} // namespace Track8::Miner