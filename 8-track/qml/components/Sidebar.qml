import QtQuick
import Track8

Rectangle {
    anchors.left: parent.left
    anchors.top: parent.top
    color: Theme.cream
    width: Theme.sidebarWidth

    Brand {
        id: brand
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        color: Theme.ink
        width: Theme.borderWidth
    }
}