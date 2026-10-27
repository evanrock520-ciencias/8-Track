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
}