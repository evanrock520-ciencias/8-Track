import QtQuick
import Track8

Window {
    color: Theme.cream
    height: 800
    visible: true
    width: 1280

    Sidebar {
        id: sidebar

        anchors.bottom: playbar.top
        anchors.left: parent.left
        anchors.top: parent.top
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
    }
}