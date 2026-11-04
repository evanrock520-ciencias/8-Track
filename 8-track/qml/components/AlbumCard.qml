import QtQuick
import QtQuick.Layouts
import Track8

NeobrutalistBox {
    id: root

    property string album
    property int year
    property url cover
    property var action

    implicitHeight: Theme.albumCardHeight
    implicitWidth: Theme.albumCardWidth
    radius: Theme.buttonRadius
    shadowOffset: hover.hovered ? Theme.shadowOffset + 2 : Theme.shadowOffset

    Behavior on shadowOffset {
        NumberAnimation {
            duration: 90
            easing.type: Easing.OutCubic
        }
    }

    HoverHandler {
        id: hover
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Item {
            Layout.alignment: Qt.AlignCenter
            implicitHeight: Theme.albumImageSize
            implicitWidth: Theme.albumImageSize

            Rectangle {
                anchors.fill: parent
                border.color: Theme.ink
                border.width: Theme.borderWidth
                color: Theme.cream
            }
            Image {
                anchors.fill: parent
                anchors.margins: Theme.borderWidth
                asynchronous: true
                fillMode: Image.PreserveAspectCrop
                mipmap: true
                source: root.cover
                sourceSize.height: Theme.albumImageSize
                sourceSize.width: Theme.albumImageSize
            }
            Rectangle {
                anchors.fill: parent
                color: Theme.ink
                opacity: hover.hovered ? 0.15 : 0

                Behavior on opacity {
                    NumberAnimation {
                        duration: 90
                    }
                }
            }
            RowPlayButton {
                anchors.centerIn: parent
                visible: hover.hovered
                onClicked: if (root.action)
                    root.action()
            }
            Tag {
                visible: root.year > 0
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.margins: 6
                text: root.year.toString()
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.leftMargin: Theme.albumCardBottonSpacingX
            Layout.rightMargin: Theme.albumCardBottonSpacingX
            color: Theme.cream
            implicitHeight: Theme.albumCardBottonHeight

            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                color: Theme.ink
                height: Theme.borderWidth
            }
            ColumnLayout {
                anchors.fill: parent
                spacing: 0

                Text {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.albumNameFontSize
                    font.weight: 800
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.WordWrap
                    text: album
                    maximumLineCount: 2
                    elide: Text.ElideRight
                }
            }
        }
    }
}
