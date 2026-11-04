import QtQuick
import Track8
import Track8.Backend 1.0

Item {
    Component.onCompleted: Library.loadAlbums()

    GridView {
        anchors.fill: parent
        anchors.margins: Theme.albumsGridMargin

        model: Library.albums
        clip: true

        cellWidth: Theme.albumCardWidth + Theme.albumsGridSpacing
        cellHeight: Theme.albumCardHeight + Theme.albumsGridSpacing

        delegate: AlbumCard {
            album: model.name
            year: model.year
        }
    }
}
