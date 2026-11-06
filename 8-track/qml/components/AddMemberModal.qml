import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Popup {
    id: root

    function setMemberSelected(id, checked) {
        const ids = selectedMembers.slice();

        if (checked && !ids.includes(id))
            ids.push(id);
        else if (!checked) {
            const index = ids.indexOf(id);
            if (index !== -1)
                ids.splice(index, 1);
        }

        selectedMembers = ids;
    }

    property int bandId
    property var currentMembers: []
    property var selectedMembers: []

    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    modal: true
    padding: 0
    width: Theme.modalWidth
    height: Theme.modalHeight

    onAboutToShow: {
        Library.loadArtists();
        currentMembers = Array.from(Library.members(bandId));
        selectedMembers = currentMembers.slice();
    }

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
                anchors.leftMargin: Theme.modalPaddingX
                anchors.rightMargin: Theme.modalPaddingX
                spacing: Theme.modalHeaderSpacing

                Image {
                    Layout.alignment: Qt.AlignVCenter
                    source: "qrc:/qt/qml/Track8/resources/icons/artist.svg"
                    sourceSize: Qt.size(Theme.modalHeaderIconSize, Theme.modalHeaderIconSize)
                }
                Text {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                    color: Theme.ink
                    font.family: Theme.fontFamily
                    font.pixelSize: Theme.modalTitleSize
                    font.weight: Font.Black
                    text: "Select Members"
                }
            }
        }

        ListView {
            id: artistList

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: Theme.songTableMargin
            clip: true
            model: Library.artists

            ScrollBar.vertical: ScrollBar {}
            delegate: ArtistRow {
                name: model.name
                selected: root.selectedMembers.includes(model.performerId)
                width: ListView.view.width

                onToggled: function (checked) {
                    root.setMemberSelected(model.performerId, checked);
                }
            }
        }

        RowLayout {}
        NeobrutalistButton {
            text: "Update Members"
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: Theme.modalPaddingX
            Layout.bottomMargin: Theme.modalPaddingX
            onClicked: {
                Library.updateMembers(bandId, selectedMembers);
                root.close();
            }
        }
    }
}
