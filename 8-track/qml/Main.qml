import QtQuick
import Track8

Window {
    id: window

    property string currentSection: "overview"
    readonly property var sectionTitles: ({
            overview: "Overview",
            albums: "Albums",
            artists: "Artists",
            songs: "Songs",
            genres: "Genres",
            bands: "Bands",
            people: "People",
            unknown: "Unknown"
        })

    color: Theme.cream
    height: 800
    visible: true
    width: 1280

    Sidebar {
        id: sidebar

        anchors.bottom: playbar.top
        anchors.left: parent.left
        anchors.top: parent.top
        currentSection: window.currentSection

        onSectionSelected: function (section) {
            window.currentSection = section;
        }
    }
    Playbar {
        id: playbar

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
    Topbar {
        id: topbar

        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.top: parent.top
        title: window.sectionTitles[window.currentSection] ?? "Overview"
    }
    ContentArea {
        id: content
        anchors.bottom: playbar.top
        anchors.left: sidebar.right
        anchors.right: parent.right
        anchors.top: topbar.bottom
        section: window.currentSection
    }
}
