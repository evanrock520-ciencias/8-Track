import QtQuick
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

RowLayout {
    id: root

    property bool connected: true
    spacing: 8

    Rectangle {
        Layout.alignment: Qt.AlignVCenter
        Layout.preferredHeight: 8
        Layout.preferredWidth: 8
        color: root.connected ? Theme.green : Theme.red
        radius: width / 2

        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }
    }
    Text {
        color: Theme.grey
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.statusFontSize
        text: root.connected ? "Connected" : "Disconnected"
    }
}
