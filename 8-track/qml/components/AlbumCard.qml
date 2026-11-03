import QtQuick
import QtQuick.Layouts
import Track8

NeobrutalistBox {
    id: root

    implicitHeight: Theme.albumCardHeight
    implicitWidth: Theme.albumCardWidth

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.alignment: Qt.AlignCenter
            implicitHeight: Theme.albumImageSize
            implicitWidth: Theme.albumImageSize

            Image {
                anchors.fill: parent
                source: "qrc:/qt/qml/Track8/resources/images/cover.png"
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
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.albumNameFontSize
                    text: "Alvvays"
                }
                Text {
                    color: Theme.grey
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.albumArtistNameFontSize
                    text: "Alvvays"
                }
                Text {
                    color: Theme.grey
                    font.family: Theme.monoFontFamily
                    font.pixelSize: Theme.albumYearFontSize
                    text: "2014"
                }
            }
        }
    }
}
