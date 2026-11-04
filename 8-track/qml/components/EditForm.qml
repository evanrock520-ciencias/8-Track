import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Popup {
    id: root

    property url cover
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
        spacing: 10

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: Theme.modalHeaderHeight
            border.color: Theme.ink
            border.width: Theme.borderWidth
            color: Theme.orange

            RowLayout {
                anchors.fill: parent
                anchors.margins: Theme.modalPaddingX
                spacing: Theme.modalHeaderSpacing

                Image {
                    Layout.alignment: Qt.AlignVCenter
                    source: "qrc:/qt/qml/Track8/resources/icons/edit.svg"
                    sourceSize: Qt.size(Theme.modalHeaderIconSize, Theme.modalHeaderIconSize)
                }
                Text {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    color: Theme.ink
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.modalTitleSize
                    font.weight: Font.Black
                    text: "Edit Performer"
                }
            }
        }
        RowLayout {
            Layout.alignment: Qt.AlignCenter
            Layout.fillWidth: true

            ColumnLayout {
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true

                Item {
                    Layout.alignment: Qt.AlignCenter
                    implicitHeight: Theme.editPerformerImageSize
                    implicitWidth: Theme.editPerformerImageSize

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
                        sourceSize.height: Theme.editPerformerImageSize
                        sourceSize.width: Theme.editPerformerImageSize
                    }
                }
            }
        }
    }
}
