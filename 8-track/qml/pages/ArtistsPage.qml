import QtQuick
import Track8
import Track8.Backend 1.0

Item {
    Component.onCompleted: Library.loadPerformers()

    GridView {
        anchors.fill: parent
        anchors.margins: Theme.albumsGridMargin
        cellHeight: Theme.albumCardHeight + Theme.albumsGridSpacing
        cellWidth: Theme.albumCardWidth + Theme.albumsGridSpacing
        clip: true
        model: Library.performers

        delegate: AlbumCard {
            album: model.name
            // cover: Library.albumCover(model.path, model.name)
        }
    }
}
