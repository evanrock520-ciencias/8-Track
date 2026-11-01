import QtQuick
import QtQuick.Controls.Basic
import Track8
import Track8.Backend 1.0

Item {
    Component.onCompleted: Library.loadSongs()

    Rectangle {
        anchors.fill: parent
        color: Theme.cream
    }

    ListView {
        id: songsList

        anchors.fill: parent
        anchors.margins: Theme.songTableMargin
        clip: true
        model: Library.songs

        header: SongTableHeader {
            width: songsList.width
            z: 2
        }

        ScrollBar.vertical: ScrollBar {}
        delegate: SongRow {
            title: model.title
            artist: model.artist
            album: model.album
            year: model.year

            width: ListView.view.width
        }
    }
}
