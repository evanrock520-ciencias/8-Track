import QtQuick
import QtQuick.Layouts
import Track8

RowLayout {
    id: root

    property int duration: 0       // ms
    property int position: 0       // ms
    signal seekRequested(int ms)

    spacing: Theme.progressSpacing

    Text {
        Layout.preferredWidth: Theme.progressTimeWidth
        color: Theme.cream
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.progressTimeFontSize
        font.weight: Theme.progressTimeWeight
        horizontalAlignment: Text.AlignRight
        text: Utils.formatTime(root.position)
    }
    NeobrutalistSlider {
        Layout.alignment: Qt.AlignVCenter
        Layout.fillWidth: true
        to: Math.max(1, root.duration)
        value: root.position

        onMoved: root.seekRequested(value)
    }
    Text {
        Layout.preferredWidth: Theme.progressTimeWidth
        color: Theme.cream
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.progressTimeFontSize
        font.weight: Theme.progressTimeWeight
        text: Utils.formatTime(root.duration)
    }
}
