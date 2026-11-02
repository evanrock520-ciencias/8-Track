import QtQuick
import QtQuick.Controls.Basic
import Track8
import Track8.Backend 1.0

Item {
    Rectangle {
        anchors.fill: parent
        color: Theme.cream
    }
    ListView {
        id: songsList

        anchors.fill: parent
        anchors.margins: Theme.songTableMargin
        clip: true
        model: Library.searchResults

        ScrollBar.vertical: ScrollBar {}
        delegate: SongRow {
            album: model.album
            artist: model.artist
            title: model.title
            width: ListView.view.width
            year: model.year
        }
        header: SongTableHeader {
            width: songsList.width
            z: 2
        }
    }
}
