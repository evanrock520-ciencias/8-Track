import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Rectangle {
    id: root

    property string currentSection: "overview"

    anchors.left: parent.left
    anchors.top: parent.top
    color: Theme.cream
    width: Theme.sidebarWidth

    signal sectionSelected(string section)

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        color: Theme.ink
        width: Theme.borderWidth
    }
    ColumnLayout {
        anchors.fill: parent
        anchors.rightMargin: Theme.borderWidth
        spacing: 0

        Brand {
            Layout.fillWidth: true
            Layout.preferredHeight: Theme.brandHeight
        }
        NavSection {
            Layout.fillWidth: true
            Layout.leftMargin: Theme.sidebarPaddingX
            Layout.rightMargin: Theme.sidebarPaddingX
            Layout.topMargin: Theme.navPaddingTop
            currentSection: root.currentSection
            model: [
                {
                    label: "Overview",
                    count: -1,
                    icon: "icons",
                    section: "overview"
                },
                {
                    label: "Albums",
                    count: Library.albumCount,
                    icon: "cd",
                    section: "albums"
                },
                {
                    label: "Artists",
                    count: Library.performerCount,
                    icon: "microphone",
                    section: "artists"
                },
                {
                    label: "Songs",
                    count: Library.songCount,
                    icon: "list-music",
                    section: "songs"
                },
                {
                    label: "Genres",
                    count: Library.genreCount,
                    icon: "icons",
                    section: "genres"
                }
            ]
            title: "LIBRARY"

            onSectionSelected: function (section) {
                root.sectionSelected(section);
            }
        }
        NavSection {
            Layout.fillWidth: true
            Layout.leftMargin: Theme.sidebarPaddingX
            Layout.rightMargin: Theme.sidebarPaddingX
            Layout.topMargin: Theme.navPaddingTop
            currentSection: root.currentSection
            model: [
                {
                    label: "Bands",
                    count: Library.bandCount,
                    icon: "band",
                    section: "bands"
                },
                {
                    label: "People",
                    count: Library.personCount,
                    icon: "artist",
                    section: "people"
                },
                {
                    label: "Unknown",
                    count: Library.unknownCount,
                    icon: "artist",
                    section: "unknown"
                }
            ]
            title: "ENTITIES"

            onSectionSelected: function (section) {
                root.sectionSelected(section);
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
