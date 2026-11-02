#pragma once
#include "Covers.hpp"
#include "mpeg/id3v2/frames/attachedpictureframe.h"
#include "mpeg/id3v2/id3v2tag.h"

#include <filesystem>
#include <initializer_list>
#include <unordered_set>

using PicType = TagLib::ID3v2::AttachedPictureFrame::Type;

namespace Track8::Miner {

/**
 * @class CoverMiner
 * @brief Extrae las carátulas de artista y álbum de un archivo `mp3` con tags
 * ID3V2.4.
 */
class CoverMiner {
public:
    explicit CoverMiner(std::filesystem::path cacheDirectory);

    [[nodiscard]] Covers coverExtract(const std::filesystem::path& path,
                                      const std::string& artistName,
                                      const std::string& albumName);

private:
    TagLib::ByteVector findPicture(const TagLib::ID3v2::FrameList& frames,
                                   std::initializer_list<PicType> types);
    std::filesystem::path pathFor(const std::string& key) const;
    void write(const std::filesystem::path& out, std::string_view data) const;

    std::filesystem::path m_cacheDirectory;
    std::unordered_set<std::string> m_tried;
};

} // namespace Track8::Miner