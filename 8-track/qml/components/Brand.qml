import QtQuick
import QtQuick.Controls
import Track8

Pane {
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.top: parent.top
    bottomPadding: Theme.brandPaddingY
    height: Theme.brandHeight
    leftPadding: Theme.brandPaddingX
    rightPadding: Theme.brandPaddingX
    topPadding: Theme.brandPaddingY

    background: Rectangle {
        color: Theme.orange

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: Theme.ink
            height: Theme.borderWidth
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.top: parent.top
            color: Theme.ink
            width: Theme.borderWidth
        }
    }
}