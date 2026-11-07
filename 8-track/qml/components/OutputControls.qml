import QtQuick
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Item {
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.outputControlsPaddingX
        anchors.rightMargin: Theme.outputControlsPaddingX
        spacing: Theme.outputControlsSpacing

        VolumeControl {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            onVolumeRequest: volume => Playback.setVolume(volume)
        }
        SimpleButton {
            Layout.alignment: Qt.AlignVCenter
            icon.source: "qrc:/qt/qml/Track8/resources/icons/list-music.svg"
        }
    }
}
