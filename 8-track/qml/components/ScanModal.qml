import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8

Popup {
    id: root

    property string directory

    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    modal: true
    padding: 0
    width: Theme.modalWidth

    background: NeobrutalistBox {
        radius: 4
        shadowOffset: 8
    }
    contentItem: ColumnLayout {
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: Theme.modalHeaderHeight
            border.color: Theme.ink
            border.width: Theme.borderWidth
            color: Theme.orange

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: Theme.modalPaddingX
                anchors.rightMargin: Theme.modalPaddingX
                spacing: Theme.modalHeaderSpacing

                Image {
                    Layout.alignment: Qt.AlignVCenter
                    source: "qrc:/qt/qml/Track8/resources/icons/scan.svg"
                    sourceSize: Qt.size(Theme.modalHeaderIconSize, Theme.modalHeaderIconSize)
                }
                Text {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    color: Theme.ink
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.modalTitleSize
                    font.weight: Font.Black
                    text: "Scan directory"
                }
            }
        }
        RowLayout {
            ColumnLayout {
                Layout.fillWidth: true
                Layout.margins: Theme.modalPaddingX
                spacing: Theme.labelSpacing

                Text {
                    color: Theme.grey
                    font.family: Theme.monoFontFamily
                    font.pixelSize: 10
                    text: "SELECTED DIRECTORY"
                }
                InfoBox {
                    Layout.fillWidth: true
                    iconSource: "qrc:/qt/qml/Track8/resources/icons/folder.svg"
                    text: root.directory
                }

                NeobrutalistButton {
                    Layout.alignment: Qt.AlignRight
                    text: "CLOSE"

                    onClicked: root.close()
                }
            }
        }
    }
}
