import QtQuick
import QtQuick.Layouts
import Track8

Rectangle {
    id: root

    property string title: "Overview"

    anchors.left: sidebar.right
    anchors.right: parent.right
    color: Theme.cream
    height: Theme.topbarHeight

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: Theme.ink
        height: Theme.borderWidth
    }
    ColumnLayout {
        anchors.bottomMargin: 16
        anchors.fill: parent
        anchors.leftMargin: 24
        anchors.rightMargin: 24
        anchors.topMargin: 14
        spacing: 12

        RowLayout {
            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            Text {
                Layout.fillWidth: true
                font.family: Theme.fontFamily
                font.pixelSize: Theme.trackFontSize
                font.weight: Theme.trackFontWeight
                text: root.title
            }

            RowLayout {
                Layout.alignment: Qt.AlignVCenter
                spacing: 12

                StatusIndicator {}
                NeobrutalistButton {
                    icon.height: Theme.buttonIconSize
                    icon.source: "qrc:/qt/qml/Track8/resources/icons/scan.svg"
                    icon.width: Theme.buttonIconSize
                    text: "SCAN"
                }
            }
        }
        Item {
            Layout.fillHeight: true
        }
    }
}
