import QtQuick
import QtQuick.Layouts
import Track8

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
            }
            StateButton {}
            SimpleButton {
                icon.source: "qrc:/qt/qml/Track8/resources/icons/skip-forward.svg"
            }
        }
        PlaybackProgress {
            Layout.fillWidth: true
            duration: 315000
            position: 138000
        }
    }
}
