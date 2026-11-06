import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Controls.impl
import QtQuick.Layouts
import Track8

Item {
    id: root

    property string name
    property alias selected: memberCheck.checked

    signal toggled(bool selected)

    implicitHeight: Theme.songRowHeight

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: Theme.ink
        height: Theme.borderWidth
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.songRowPaddingX
        anchors.rightMargin: Theme.songRowPaddingX
        spacing: Theme.songRowSpacing

        CheckBox {
            id: memberCheck

            Layout.alignment: Qt.AlignVCenter
            implicitWidth: Theme.rowPlayButtonSize
            implicitHeight: Theme.rowPlayButtonSize
            padding: 0
            hoverEnabled: true
            Accessible.name: root.name
            onToggled: root.toggled(checked)

            indicator: NeobrutalistBox {
                readonly property real press: memberCheck.down ? Theme.shadowOffset : 0

                width: Theme.rowPlayButtonSize
                height: Theme.rowPlayButtonSize
                radius: Theme.buttonRadius
                color: memberCheck.checked ? Theme.blue : (memberCheck.hovered ? Theme.yellow : Theme.cream)
                border.width: memberCheck.activeFocus ? Theme.borderWidth + 1 : Theme.borderWidth
                shadowOffset: Theme.shadowOffset - press
                x: press
                y: press

                IconImage {
                    anchors.centerIn: parent
                    width: Theme.rowPlayIconSize
                    height: Theme.rowPlayIconSize
                    source: "qrc:/qt/qml/Track8/resources/icons/check.svg"
                    sourceSize: Qt.size(width, height)
                    color: Theme.cream
                    visible: memberCheck.checked
                }
            }
        }

        Text {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColTitleWidth
            color: Theme.ink
            elide: Text.ElideRight
            font.family: Theme.fontFamily
            font.pixelSize: Theme.songColTitleFontSize
            text: root.name
        }
    }
}
