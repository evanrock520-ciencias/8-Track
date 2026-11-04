import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import Track8

AbstractButton {
    id: root

    readonly property real press: down ? Theme.shadowOffset : 0

    display: AbstractButton.IconOnly
    hoverEnabled: true
    icon.color: Theme.ink
    icon.height: Theme.rowPlayIconSize
    icon.source: "qrc:/qt/qml/Track8/resources/icons/play.svg"
    icon.width: Theme.rowPlayIconSize
    implicitHeight: Theme.rowPlayButtonSize
    implicitWidth: Theme.rowPlayButtonSize

    background: NeobrutalistBox {
        border.width: Theme.rowPlayBorderWidth
        color: root.hovered ? Theme.blue : Theme.cream
        radius: width / 2
        shadowOffset: Theme.shadowOffset - root.press
        x: root.press
        y: root.press
    }
    contentItem: IconLabel {
        display: root.display
        icon: root.icon

        transform: Translate {
            x: root.press
            y: root.press
        }
    }
}
