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

    Image {
        id: tape
        source: "qrc:/qt/qml/Track8/resources/icons/tape.svg"
    }

    Text {
        anchors.left: tape.right
        anchors.leftMargin: 10
        text: "8-Track"
        font.family: Theme.fontFamily
        font.pixelSize: Theme.trackFontSize
        font.weight: Theme.trackFontWeight
    }
}
