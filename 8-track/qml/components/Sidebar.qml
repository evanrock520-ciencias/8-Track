import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Rectangle {
    anchors.left: parent.left
    anchors.top: parent.top
    color: Theme.cream
    width: Theme.sidebarWidth

    ButtonGroup {
        id: navGroup
    }

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
            group: navGroup
            model: [
                {
                    label: "Overview",
                    count: -1,
                    icon: "icons"
                },
                {
                    label: "Albums",
                    count: Library.albumCount,
                    icon: "cd"
                },
                {
                    label: "Artists",
                    count: Library.performerCount,
                    icon: "microphone"
                },
                {
                    label: "Songs",
                    count: Library.songCount,
                    icon: "list-music"
                },
                {
                    label: "Genres",
                    count: Library.genreCount,
                    icon: "icons"
                }
            ]
            title: "LIBRARY"
        }
        NavSection {
            Layout.fillWidth: true
            Layout.leftMargin: Theme.sidebarPaddingX
            Layout.rightMargin: Theme.sidebarPaddingX
            Layout.topMargin: Theme.navPaddingTop
            group: navGroup
            model: [
                {
                    label: "Bands",
                    count: Library.bandCount,
                    icon: "band"
                },
                {
                    label: "People",
                    count: Library.personCount,
                    icon: "artist"
                },
                {
                    label: "Unknown",
                    count: Library.unknownCount,
                    icon: "artist"
                }
            ]
            title: "ENTITIES"
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
