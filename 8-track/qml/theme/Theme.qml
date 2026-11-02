pragma Singleton
import QtQuick

QtObject {
    // Colores
    readonly property color blue: "#2F63E9"
    readonly property color cream: "#FFFDF7"
    readonly property color ink: "#151515"
    readonly property color grey: "#67635C"
    readonly property color orange: "#FF5C35"
    readonly property color yellow: "#F6C945"
    readonly property color green: "#22C55E"
    readonly property color red: "#D9382A"
    readonly property color ambar: "#E7972E"

    readonly property int shadowOffset: 3
    readonly property int borderWidth: 2

    // Tipografía
    readonly property FontLoader interLoader: FontLoader {
        source: "../resources/fonts/Inter-Variable.ttf"
    }
    readonly property FontLoader monoLoader: FontLoader {
        source: "../resources/fonts/RobotoMono-Variable.ttf"
    }

    readonly property string fontFamily: interLoader.name
    readonly property string monoFontFamily: monoLoader.name

    // Medidas
    // Playbar
    readonly property int playbarHeight: 112

    // Topbar
    readonly property int topbarHeight: 132

    // Sidebar
    readonly property int sidebarWidth: 224
    readonly property int sidebarPaddingX: 14

    // Brand
    readonly property int brandHeight: 126
    readonly property int brandPaddingX: 18
    readonly property int brandPaddingY: 16

    readonly property int trackFontSize: 28
    readonly property int trackFontWeight: 900

    // Status Indicator
    readonly property int statusFontSize: 10

    // Buttons
    readonly property int buttonPaddingX: 10
    readonly property int buttonHeight: 32
    readonly property int buttonFontSize: 11
    readonly property int buttonSpacing: 8
    readonly property int buttonRadius: 4
    readonly property int buttonIconSize: 14

    // Search Bar
    readonly property int searchBarFontSize: 14
    readonly property int searchBarFontWeight: 400
    readonly property int searchBarHeight: 44
    readonly property int searchBarPaddingX: 8
    readonly property int searchBarRadius: 8
    readonly property int lensIconSize: 20

    // Nav Item
    readonly property int navBarItemHeight: 42
    readonly property int navBarItemWidth: 196
    readonly property int navBarItemPaddingX: 12
    readonly property int navBarItemSpacing: 10
    readonly property int navBarItemFontSize: 14
    readonly property int navBarItemCountSize: 10
    readonly property int navPaddingTop: 18
    readonly property int navSpacing: 4
    readonly property int navBarItemIconSize: 18

    // Play bar
    // Now Playing
    readonly property int nowPlayingWidth: 360
    readonly property int nowPlayingPadding: 14
    readonly property int nowPlayingSpacing: 12
    readonly property int nowPlayingCoverSize: 84
    readonly property int nowPlayingTitleFontSize: 16
    readonly property int nowPlayingSubtitleFontSize: 12
    readonly property int playbarBorderWidth: 1

    // Tag
    readonly property int tagPaddingX: 7
    readonly property int tagPaddingY: 3
    readonly property int tagHeight: 13
    readonly property int tagRadius: 4
    readonly property int tagFontSize: 10

    // Track Control
    // Playback Button
    readonly property int playbackButtonRadius: 42
    readonly property int playbackButtonIconSize: 20
    readonly property int trackControlWidth: 750
    readonly property int trackControlPaddingX: 36
    readonly property int trackControlPaddingY: 12
    readonly property int trackControlSpacing: 10
    readonly property int playbackButtonSpacing: 18
    readonly property int playerIconSize: 17
    readonly property int playerButtonSize: 28

    // Playback Progress
    readonly property int progressHeight: 8
    readonly property int progressBorderWidth: 1
    readonly property int progressSpacing: 10
    readonly property int progressTimeWidth: 36
    readonly property int progressTimeFontSize: 10
    readonly property int progressTimeWeight: 700

    // Volume
    readonly property int volumeSpacing: 8
    readonly property int volumeValueWidth: 20
    readonly property int volumeSliderWidth: 127
    readonly property int outputControlsWidth: 330
    readonly property int outputControlsPaddingX: 18
    readonly property int outputControlsSpacing: 16

    // Song Row
    readonly property int songRowHeight: 42
    readonly property int songRowPaddingX: 10
    readonly property int songRowSpacing: 10
    readonly property int songColPlayWidth: 24
    readonly property int songColTitleWidth: 180
    readonly property int songColArtistWidth: 120
    readonly property int songColAlbumWidth: 180
    readonly property int songColYearWidth: 40
    readonly property int songColFormatWidth: 40
    readonly property int songColTimeWidth: 40
    readonly property int songColMenuWidth: 24
    readonly property int songColTitleFontSize: 14
    readonly property int songColSubtitlesFontSize: 14
    readonly property int rowPlayButtonSize: 24
    readonly property int rowPlayIconSize: 12
    readonly property int rowPlayBorderWidth: 1

    // Song Table
    readonly property int songTableMargin: 22
    readonly property int songHeaderHeight: 28

    // Modal
    readonly property int modalWidth: 620
    readonly property int modalHeight: 387
    readonly property int modalPaddingX: 20
    readonly property int modalHeaderHeight: 58
    readonly property int modalHeaderSpacing: 10
    readonly property int modalHeaderIconSize: 20
    readonly property int modalTitleSize: 20

    // Info Box
    readonly property int infoBoxHeight: 42
    readonly property int infoBoxRadius: 4
    readonly property int infoBoxPaddingX: 12
    readonly property int infoBoxSpacing: 10
    readonly property int infoBoxIconSize: 17
    readonly property int infoBoxFontSize: 11

    readonly property int labelSpacing: 12
}
