import QtQuick
import QtQuick.Controls.Basic
import Track8

ProgressBar {
    id: root

    property color fillColor: Theme.blue
    property color trackColor: Theme.cream

    from: 0
    implicitHeight: Theme.progressBarHeight
    to: 1

    background: Rectangle {
        border.color: Theme.ink
        border.width: Theme.borderWidth
        color: root.trackColor
    }
    contentItem: Item {
        Rectangle {
            color: root.fillColor
            height: parent.height
            visible: !root.indeterminate
            width: root.visualPosition * parent.width
        }

        Rectangle {
            id: block

            color: root.fillColor
            height: parent.height
            visible: root.indeterminate
            width: parent.width * 0.25

            SequentialAnimation on x {
                loops: Animation.Infinite
                running: root.indeterminate && root.visible

                NumberAnimation {
                    duration: 1000
                    from: 0
                    to: block.parent.width - block.width
                }
                NumberAnimation {
                    duration: 1000
                    from: block.parent.width - block.width
                    to: 0
                }
            }
        }
    }
}
