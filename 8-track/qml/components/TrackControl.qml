import QtQuick
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Item {
    id: root

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        color: Theme.grey
        width: Theme.playbarBorderWidth
    }
    ColumnLayout {
        anchors.bottomMargin: Theme.trackControlPaddingY
        anchors.fill: parent
        anchors.leftMargin: Theme.trackControlPaddingX
        anchors.rightMargin: Theme.trackControlPaddingX
        anchors.topMargin: Theme.trackControlPaddingY
        spacing: Theme.trackControlSpacing

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: Theme.playbackButtonSpacing

            SimpleButton {
                checkable: true
                icon.source: "qrc:/qt/qml/Track8/resources/icons/shuffle.svg"
            }
            SimpleButton {
                icon.source: "qrc:/qt/qml/Track8/resources/icons/skip-back.svg"
                onClicked: Playback.previous()
            }
            StateButton {
                onClicked: Playback.togglePlayback()
            }
            SimpleButton {
                icon.source: "qrc:/qt/qml/Track8/resources/icons/skip-forward.svg"
                onClicked: Playback.next()
            }
        }
        PlaybackProgress {
            Layout.fillWidth: true
            duration: Playback.duration
            position: Playback.position
        }
    }
}
