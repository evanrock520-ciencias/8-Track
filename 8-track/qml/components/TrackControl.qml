import QtQuick
import QtQuick.Layouts
import Track8

Item {
    id: root

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        color: Theme.grey
        width: Theme.playbarBorderWidth
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.trackControlPaddingX
        anchors.rightMargin: Theme.trackControlPaddingX
        anchors.topMargin: Theme.trackControlPaddingY
        anchors.bottomMargin: Theme.trackControlPaddingY
        spacing: Theme.trackControlSpacing

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: Theme.playbackButtonSpacing

            SimpleButton {
                icon.source: "qrc:/qt/qml/Track8/resources/icons/shuffle.svg"
                checkable: true
            }
            SimpleButton {
                icon.source: "qrc:/qt/qml/Track8/resources/icons/skip-back.svg"
            }
            StateButton {}
            SimpleButton {
                icon.source: "qrc:/qt/qml/Track8/resources/icons/skip-forward.svg"
            }
        }
        Item {
            // TODO: Añadir barra de reproducción
            Layout.fillHeight: true
        }
    }
}
