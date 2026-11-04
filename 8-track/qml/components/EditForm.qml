import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Popup {
    id: root

    property url cover
    property string directory
    property string name
    property int type
    property int selectedType: type

    function openFor(performer) {
        name = performer.name;
        cover = Library.performerCover(performer.name);
        type = performer.type;
        selectedType = performer.type;
        open();
    }

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

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 8

            ButtonGroup {
                id: performerTypeGroup
            }

            NeobrutalistButton {
                ButtonGroup.group: performerTypeGroup
                checkable: true
                checked: root.selectedType === 2
                onClicked: root.selectedType = 2
                fillColor: checked ? Theme.blue : Theme.cream
                icon.source: "qrc:/qt/qml/Track8/resources/icons/unknown.svg"
                display: AbstractButton.IconOnly
            }

            NeobrutalistButton {
                ButtonGroup.group: performerTypeGroup
                checkable: true
                checked: root.selectedType === 0
                onClicked: root.selectedType = 0
                fillColor: checked ? Theme.blue : Theme.cream
                icon.source: "qrc:/qt/qml/Track8/resources/icons/artist.svg"
                display: AbstractButton.IconOnly
            }

            NeobrutalistButton {
                ButtonGroup.group: performerTypeGroup
                checkable: true
                checked: root.selectedType === 1
                onClicked: root.selectedType = 1
                fillColor: checked ? Theme.blue : Theme.cream
                icon.source: "qrc:/qt/qml/Track8/resources/icons/band.svg"
                display: AbstractButton.IconOnly
            }
        }

        Loader {
            id: fieldsLoader
            Layout.fillWidth: true
            Layout.leftMargin: Theme.modalPaddingX
            Layout.rightMargin: Theme.modalPaddingX

            sourceComponent: {
                switch (root.selectedType) {
                case 0:
                    return artistFields;
                case 1:
                    return bandFields;
                default:
                    return unknownFields;
                }
            }
        }

        Component {
            id: artistFields
            ColumnLayout {
                width: parent.width
                Layout.alignment: Qt.AlignCenter
                spacing: 8

                Tag {
                    Layout.alignment: Qt.AlignCenter
                    text: "Stage Name"
                    size: 14
                }

                NeobrutalistInput {
                    value: root.name
                    placeholder: "Artist stage name"
                }

                Tag {
                    Layout.alignment: Qt.AlignCenter
                    text: "Real Name"
                    size: 14
                }

                NeobrutalistInput {
                    value: ""
                    placeholder: "Artist real name"
                }
            }
        }

        Component {
            id: bandFields
            ColumnLayout {
                spacing: 8

                Tag {
                    Layout.alignment: Qt.AlignCenter
                    text: "Name"
                    size: 14
                }

                NeobrutalistInput {
                    value: root.name
                    placeholder: "Group name"
                }
            }
        }

        Component {
            id: unknownFields
            ColumnLayout {
                spacing: 8

                Tag {
                    Layout.alignment: Qt.AlignCenter
                    text: "Name"
                    size: 14
                }

                NeobrutalistInput {
                    value: root.name
                    placeholder: "Performer name"
                }
            }
        }

        NeobrutalistButton {
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: Theme.modalPaddingX
            Layout.bottomMargin: Theme.modalPaddingX
            icon.source: "qrc:/qt/qml/Track8/resources/icons/forward.svg"
            text: "Apply Changes"
        }
    }
}
