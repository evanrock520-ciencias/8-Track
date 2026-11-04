import QtQuick
import QtQuick.Layouts
import Track8

NeobrutalistBox {
    id: root

    property string text
    property color textColor: Theme.ink
    property int size: Theme.tagFontSize

    color: Theme.yellow
    implicitHeight: Theme.tagHeight + Theme.tagPaddingY * 2
    implicitWidth: label.implicitWidth + Theme.tagPaddingX * 2
    radius: Theme.tagRadius
    shadowEnabled: false

    Text {
        id: label

        anchors.centerIn: parent
        color: root.textColor
        font.family: Theme.monoFontFamily
        font.pixelSize: root.size
        font.weight: Font.Bold
        text: root.text
    }
}
