#include "miner/CoverMiner.hpp"

#include "mpegfile.h"
#include "picosha2.h"
#include <fstream>
#include <utility>

namespace Track8::Miner {

CoverMiner::CoverMiner(std::filesystem::path cacheDirectory)
    : m_cacheDirectory(std::move(cacheDirectory)) {}

TagLib::ByteVector
CoverMiner::findPicture(const TagLib::ID3v2::FrameList& frames,
                        const std::initializer_list<PicType> types) {
    for (const auto type : types) {
        for (auto* frame : frames) {
            if (const auto* picture =
                    dynamic_cast<TagLib::ID3v2::AttachedPictureFrame*>(frame);
                picture && picture->type() == type)
                return picture->picture();
        }
    }

    return {};
}

std::filesystem::path CoverMiner::pathFor(const std::string& key) const {
    return m_cacheDirectory / (picosha2::hash256_hex_string(key) + ".jpg");
}

void CoverMiner::write(const std::filesystem::path& out,
                       const std::string_view data) const {
    if (data.empty())
        return;
    std::filesystem::create_directories(m_cacheDirectory);
    std::ofstream writer(out, std::ios::binary);
    writer.write(data.data(), static_cast<std::streamsize>(data.size()));
}

Covers CoverMiner::coverExtract(const std::filesystem::path& path,
                                const std::string& artistName,
                                const std::string& albumName) {
    const std::string albumKey = artistName + "|" + albumName;

    const auto albumPath = pathFor(albumKey);
    const auto artistPath = pathFor(artistName);

    const bool needAlbum =
        !std::filesystem::exists(albumPath) && !m_tried.contains(albumKey);
    const bool needArtist =
        !std::filesystem::exists(artistPath) && !m_tried.contains(artistName);

    if (needAlbum || needArtist) {
        m_tried.insert(albumKey);
        m_tried.insert(artistName);

        if (TagLib::MPEG::File file(path.c_str());
            file.isValid() && file.ID3v2Tag()) {
            if (const auto& frames = file.ID3v2Tag()->frameListMap()["APIC"];
                !frames.isEmpty()) {
                if (needAlbum) {
                    const auto data = findPicture(
                        frames, {PicType::FrontCover, PicType::Other});
                    write(albumPath, {data.data(), data.size()});
                }
                if (needArtist) {
                    const auto data = findPicture(
                        frames,
                        {PicType::Artist, PicType::LeadArtist, PicType::Band});
                    write(artistPath, {data.data(), data.size()});
                }
            }
        }
    }

    return {.album = std::filesystem::exists(albumPath)
                         ? albumPath
                         : std::filesystem::path{},
            .artist = std::filesystem::exists(artistPath)
                          ? artistPath
                          : std::filesystem::path{}};
}

} // namespace Track8::Miner