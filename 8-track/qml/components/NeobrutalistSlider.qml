import QtQuick
import QtQuick.Controls.Basic
import Track8

Slider {
    id: control

    property color fillColor: Theme.orange

    implicitHeight: Theme.progressHeight

    background: Rectangle {
        border.color: Theme.cream
        border.width: Theme.progressBorderWidth
        color: Theme.grey
        radius: height / 2

        Rectangle {
            color: control.fillColor
            height: parent.height - 2 * Theme.progressBorderWidth
            radius: height / 2
            width: control.visualPosition * (parent.width - 2 * Theme.progressBorderWidth)
            x: Theme.progressBorderWidth
            y: Theme.progressBorderWidth
        }
    }
    handle: Item {}
}
