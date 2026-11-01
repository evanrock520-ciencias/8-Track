import QtQuick
import QtQuick.Layouts
import Track8

Item {
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.outputControlsPaddingX
        anchors.rightMargin: Theme.outputControlsPaddingX
        spacing: Theme.outputControlsSpacing

        VolumeControl {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
        }
        SimpleButton {
            Layout.alignment: Qt.AlignVCenter
            icon.source: "qrc:/qt/qml/Track8/resources/icons/list-music.svg"
        }
    }
}
