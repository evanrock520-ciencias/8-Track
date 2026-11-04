import QtQuick
import Track8
import Track8.Backend 1.0

Item {
    Component.onCompleted: Library.loadPerformers()

    EditForm {
        id: editForm
    }

    GridView {
        anchors.fill: parent
        anchors.margins: Theme.albumsGridMargin
        cellHeight: Theme.albumCardHeight + Theme.albumsGridSpacing
        cellWidth: Theme.albumCardWidth + Theme.albumsGridSpacing
        clip: true
        model: Library.performers

        delegate: AlbumCard {
            album: model.name
            cover: Library.performerCover(model.name)
            action: () => {
                editForm.cover = Library.performerCover(model.name);
                editForm.open();
            }
        }
    }
}
