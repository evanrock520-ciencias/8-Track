import QtQuick
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Rectangle {
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    color: Theme.ink
    height: Theme.playbarHeight
    width: parent.width

    RowLayout {
        anchors.fill: parent
        spacing: 0

        NowPlaying {
            Layout.fillHeight: true
            Layout.preferredWidth: Theme.nowPlayingWidth
            cover: Playback.cover
            subtitle: `${Playback.artist} - ${Playback.album}`
            title: Playback.title
        }
        TrackControl {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        OutputControls {
            Layout.fillHeight: true
            Layout.preferredWidth: Theme.outputControlsWidth
        }
    }
}
