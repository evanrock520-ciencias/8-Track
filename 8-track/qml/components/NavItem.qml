import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8

AbstractButton {
    id: root

    property bool active: false
    property int count: -1

    checkable: false
    implicitHeight: Theme.navBarItemHeight
    leftPadding: Theme.navBarItemPaddingX
    rightPadding: Theme.navBarItemPaddingX
    spacing: Theme.navBarItemSpacing

    background: Item {
        Rectangle {
            anchors.fill: parent
            border.color: Theme.ink
            border.width: Theme.borderWidth
            color: Theme.yellow
            visible: root.active

            Behavior on opacity {
                NumberAnimation {
                    duration: 100
                }
            }
        }
        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            color: Theme.ink
            height: Theme.borderWidth
            visible: !root.active

            Behavior on opacity {
                NumberAnimation {
                    duration: 100
                }
            }
        }
    }
    contentItem: RowLayout {
        spacing: root.spacing

        Image {
            Layout.alignment: Qt.AlignVCenter
            source: root.icon.source
            sourceSize: Qt.size(root.icon.width, root.icon.height)
        }
        Text {
            Layout.fillWidth: true
            color: Theme.ink
            font.family: Theme.fontFamily
            font.pixelSize: Theme.navBarItemFontSize
            font.weight: root.active ? Font.Bold : Font.Normal
            text: root.text
        }
        Text {
            color: Theme.grey
            font.family: Theme.monoFontFamily
            font.pixelSize: Theme.navBarItemCountSize
            text: root.count.toLocaleString(Qt.locale("en_US"), "f", 0)
            visible: root.count >= 0
        }
    }
}
