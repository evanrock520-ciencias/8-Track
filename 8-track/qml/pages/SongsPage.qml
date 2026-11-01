import QtQuick
import Track8
import Track8.Backend 1.0

Item {
    Component.onCompleted: Library.loadSongs()

    Rectangle {
        anchors.fill: parent
        color: Theme.orange
    }
    Text {
        anchors.centerIn: parent
        color: Theme.ink
        font.family: Theme.fontFamily
        font.pixelSize: 24
        text: Library.songs.count + " songs"
    }
}
