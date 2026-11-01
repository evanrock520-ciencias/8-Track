import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import Track8

AbstractButton {
    id: root

    display: AbstractButton.IconOnly
    hoverEnabled: true
    icon.color: Theme.ink
    icon.height: Theme.rowPlayIconSize
    icon.source: "qrc:/qt/qml/Track8/resources/icons/play.svg"
    icon.width: Theme.rowPlayIconSize
    implicitHeight: Theme.rowPlayButtonSize
    implicitWidth: Theme.rowPlayButtonSize

    background: Rectangle {
        border.color: Theme.ink
        border.width: Theme.rowPlayBorderWidth
        color: root.hovered ? Theme.blue : "transparent"
        radius: width / 2
    }
    contentItem: IconLabel {
        display: root.display
        icon: root.icon
    }
}
