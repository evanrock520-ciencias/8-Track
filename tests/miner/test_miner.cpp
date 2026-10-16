#include "domain/Song.hpp"
#include "miner/Miner.hpp"
#include "taglib/fileref.h"
#include "taglib/tag.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <string>

using namespace Track8::Miner;

namespace {
class MinerTest : public ::testing::Test {
protected:
    const std::filesystem::path dataDir{TEST_DATA_DIR};
};
} // namespace

// El directorio tiene 4 archivos. Analizandolo con mid3v2, tenemos

// IDv2 tag info for big_time.mp3
// TALB=Big Time
// TCON=Country
// TDRC=2022
// TIT2=Big Time
// TPE1=Angel Olsen
// TSSE=Lavf60.16.100
// TXXX=comment=https://www.youtube.com/watch?v=SNX-AqNwWYk
// TXXX=description=Provided to YouTube by BWSCD Inc

// IDv2 tag info for everyday.mp3
// TALB=Titanic Rising
// TCON=Art Pop
// TDRC=2019
// TIT2=Everyday
// TPE1=Weyes Blood
// TSSE=Lavf60.16.100
// TXXX=comment=https://www.youtube.com/watch?v=Ay6_iBJV9cc
// TXXX=description=Provided to YouTube by Sub Pop Records

// IDv2 tag info for polka_dots_and_moonbeams.mp3
// TALB=
// TCON=
// TIT2=
// TPE1=
// TSSE=Lavf60.16.100

// IDv2 tag info for sense.mp3
// TALB=Paper Mâché Dream Balloon
// TCON=Folk
// TDRC=2017
// TIT2=Sense
// TPE1=King Gizzard & The Lizard Wizard
// TSSE=Lavf60.16.100
// TXXX=comment=https://www.youtube.com/watch?v=bNpEUbWOBiM
// TXXX=description=Provided to YouTube by ATO Record

TEST_F(MinerTest, MetadataWithAllTags) {
    const Metadata metadata =
        Miner::parseFile(dataDir / "songs" / "big_time.mp3");
    EXPECT_EQ(metadata.m_path, dataDir / "songs" / "big_time.mp3");
    EXPECT_EQ(metadata.m_performer, "Angel Olsen");
    EXPECT_EQ(metadata.m_title, "Big Time");
    EXPECT_EQ(metadata.m_album, "Big Time");
    EXPECT_EQ(metadata.m_year, 2022);
    EXPECT_EQ(metadata.m_genre, "Country");
}

TEST_F(MinerTest, EmptyMetadata) {
    const Metadata metadata =
        Miner::parseFile(dataDir / "songs" / "polka_dots_and_moonbeams.mp3");
    EXPECT_EQ(metadata.m_path,
              dataDir / "songs" / "polka_dots_and_moonbeams.mp3");
    EXPECT_EQ(metadata.m_performer, "Unknown");
    EXPECT_EQ(metadata.m_title, "Unknown");
    EXPECT_EQ(metadata.m_album, "Unknown");
    EXPECT_EQ(metadata.m_year, 2026);
    EXPECT_EQ(metadata.m_genre, "Unknown");
}

TEST_F(MinerTest, ScanAllFiles) {
    // En songs hay 3 canciones.
    constexpr int expectedFiles = 3;
    int currentFiles = 0;

    const Miner miner(dataDir / "songs");
    miner.mine([&currentFiles](const Metadata&) { currentFiles++; });

    EXPECT_EQ(currentFiles, expectedFiles);
}

TEST_F(MinerTest, OnlyScanMp3Files) {
    constexpr int expectedFiles = 0;
    int currentFiles = 0;

    // En datadir / "images" solo existen andromeda.jpg y cat.png
    const Miner miner(dataDir / "images");
    miner.mine([&currentFiles](const Metadata&) { currentFiles++; });

    EXPECT_EQ(currentFiles, expectedFiles);
}

TEST_F(MinerTest, ScanRecursively) {
    // En el directorio general hay 4 canciones.
    // 3 en songs y una en la raíz.
    constexpr int expectedFiles = 4;
    int currentFiles = 0;

    const Miner miner(dataDir);
    miner.mine([&currentFiles](const Metadata&) { currentFiles++; });

    EXPECT_EQ(currentFiles, expectedFiles);
}
