import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import Track8

AbstractButton {
    id: root

    property color checkedColor: Theme.blue

    checkable: false
    hoverEnabled: true
    display: AbstractButton.IconOnly
    icon.color: checked ? checkedColor : Theme.cream
    icon.height: Theme.playerIconSize
    icon.width: Theme.playerIconSize
    implicitHeight: Theme.playerButtonSize
    implicitWidth: Theme.playerButtonSize

    background: Rectangle {
        color: Theme.grey
        radius: width / 2
        visible: root.hovered
    }

    contentItem: IconLabel {
        display: root.display
        icon: root.icon
    }
}
