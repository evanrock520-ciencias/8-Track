import QtQuick
import QtQuick.Layouts
import Track8

NeobrutalistBox {
    id: root

    implicitHeight: 242
    implicitWidth: 202

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.alignment: Qt.AlignCenter
            implicitHeight: 142
            implicitWidth: 142

            Image {
                anchors.fill: parent
                source: "qrc:/qt/qml/Track8/resources/images/cover.png"
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.rightMargin: 10
            color: Theme.cream
            implicitHeight: 70

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
                    font.pixelSize: 14
                    text: "Alvvays"
                }
                Text {
                    color: Theme.grey
                    font.family: Theme.fontFamily
                    font.pixelSize: 11
                    text: "Alvvays"
                }
                Text {
                    color: Theme.grey
                    font.family: Theme.monoFontFamily
                    font.pixelSize: 10
                    text: "2014"
                }
            }
        }
    }
}
