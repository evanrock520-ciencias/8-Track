import QtQuick
import Track8

Rectangle {
    height: Theme.topbarHeight

    anchors.left: sidebar.right
    anchors.right: parent.right

    color: Theme.cream

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: Theme.ink
        height: Theme.borderWidth
    }
}