import QtQuick
import QtQuick.Layouts
import Track8

RowLayout {
    id: root

    property int volume: 74

    spacing: Theme.volumeSpacing

    Image {
        Layout.alignment: Qt.AlignVCenter
        source: "qrc:/qt/qml/Track8/resources/icons/volume.svg"
        sourceSize: Qt.size(15, 12)
    }
    NeobrutalistSlider {
        Layout.alignment: Qt.AlignVCenter
        Layout.fillWidth: true
        fillColor: Theme.yellow
        from: 0
        to: 100
        value: root.volume
    }
    Text {
        Layout.alignment: Qt.AlignVCenter
        Layout.preferredWidth: Theme.volumeValueWidth
        color: Theme.cream
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.progressTimeFontSize
        font.weight: Theme.progressTimeWeight
        text: root.volume
    }
}
