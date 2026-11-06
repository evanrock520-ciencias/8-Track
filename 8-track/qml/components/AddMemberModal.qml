import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Popup {
    id: root

    anchors.centerIn: Overlay.overlay
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
    modal: true
    padding: 0
    width: Theme.modalWidth
    height: Theme.modalHeight

    onAboutToShow: Library.loadArtists()

    background: NeobrutalistBox {
        radius: 4
        shadowOffset: 8
    }

    contentItem: ColumnLayout {
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
                width: ListView.view.width
            }
        }
    }
}
