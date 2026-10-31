import QtQuick
import QtQuick.Layouts
import Track8

Rectangle {
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    color: Theme.ink
    height: Theme.playbarHeight
    width: parent.width

    RowLayout {
        anchors.fill: parent
        spacing: 0

        NowPlaying {
            Layout.fillHeight: true
            Layout.preferredWidth: Theme.nowPlayingWidth
            cover: "qrc:/qt/qml/Track8/resources/images/cover.png"
            subtitle: "Alvvays - Alvvays"
            title: "Atop a Cake"
        }
        Item {
            // TODO: Agregar sección de control
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
        Item {
            // TODO: Agregar sección de volumen y cola
            Layout.fillHeight: true
            Layout.preferredWidth: 200
        }
    }
}
