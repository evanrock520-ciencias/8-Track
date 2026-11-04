import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import Track8

TextField {
    id: root

    property string value
    property string placeholder

    Layout.alignment: Qt.AlignCenter
    clip: true
    font.family: Theme.monoFontFamily
    font.pixelSize: 12
    font.weight: 800
    implicitHeight: 32
    implicitWidth: 242
    text: value
    placeholderText: placeholder

    background: NeobrutalistBox {
        color: Theme.cream
        shadowOffset: Theme.shadowOffset
    }
}
