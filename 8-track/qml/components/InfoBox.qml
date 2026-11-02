import QtQuick
import QtQuick.Layouts
import Track8

NeobrutalistBox {
    id: root

    property color iconColor: Theme.ink
    property url iconSource
    property string text

    implicitHeight: Theme.infoBoxHeight
    radius: Theme.infoBoxRadius
    shadowEnabled: false

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.infoBoxPaddingX
        anchors.rightMargin: Theme.infoBoxPaddingX
        spacing: Theme.infoBoxSpacing

        Image {
            Layout.alignment: Qt.AlignVCenter
            source: root.iconSource
            sourceSize: Qt.size(Theme.infoBoxIconSize, Theme.infoBoxIconSize)
        }
        Text {
            Layout.alignment: Qt.AlignVCenter
            Layout.fillWidth: true
            color: Theme.ink
            elide: Text.ElideMiddle
            font.family: Theme.monoFontFamily
            font.pixelSize: Theme.infoBoxFontSize
            text: root.text
        }
    }
}
