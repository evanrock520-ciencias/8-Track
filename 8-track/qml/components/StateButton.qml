import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import Track8

AbstractButton {
    id: root

    property color buttonColor: Theme.orange

    checkable: true
    hoverEnabled: true
    display: AbstractButton.IconOnly
    icon.color: Theme.cream
    icon.height: Theme.playbackButtonIconSize
    icon.source: checked ? "qrc:/qt/qml/Track8/resources/icons/pause.svg" : "qrc:/qt/qml/Track8/resources/icons/play.svg"
    icon.width: Theme.playbackButtonIconSize
    implicitHeight: Theme.playbackButtonRadius
    implicitWidth: Theme.playbackButtonRadius

    background: Rectangle {
        color: root.buttonColor
        radius: width / 2
        border.color: Theme.cream
        border.width: root.hovered ? Theme.borderWidth : 0
    }
    contentItem: IconLabel {
        display: root.display
        icon: root.icon
    }
}
