import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8

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
                    count: 428,
                    icon: "cd"
                },
                {
                    label: "Artists",
                    count: 196,
                    icon: "microphone"
                },
                {
                    label: "Songs",
                    count: 5842,
                    icon: "list-music"
                },
                {
                    label: "Genres",
                    count: 37,
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
                    count: 71,
                    icon: "band"
                },
                {
                    label: "People",
                    count: 125,
                    icon: "artist"
                },
                {
                    label: "Unknown",
                    count: 30,
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
