import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import Track8

AbstractButton {
    id: root

    property color fillColor: Theme.orange
    readonly property real press: down ? Theme.shadowOffset : 0
    property color textColor: Theme.ink

    bottomPadding: 0
    icon.color: textColor
    implicitHeight: Theme.buttonHeight
    leftPadding: Theme.buttonPaddingX
    rightPadding: Theme.buttonPaddingX
    spacing: Theme.buttonSpacing
    topPadding: 0

    background: NeobrutalistBox {
        color: root.fillColor
        radius: Theme.buttonRadius
        shadowOffset: Theme.shadowOffset - root.press
        x: root.press
        y: root.press
    }
    contentItem: IconLabel {
        color: root.textColor
        display: root.display
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.buttonFontSize
        font.weight: Font.Bold
        icon: root.icon
        spacing: root.spacing
        text: root.text

        transform: Translate {
            x: root.press
            y: root.press
        }
    }
}
