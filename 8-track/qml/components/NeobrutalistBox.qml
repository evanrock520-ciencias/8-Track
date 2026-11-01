import QtQuick
import Track8

Rectangle {
    id: root

    property color shadowColor: Theme.ink
    property bool shadowEnabled: true
    property int shadowOffset: Theme.shadowOffset

    border.color: Theme.ink
    border.width: Theme.borderWidth
    color: Theme.cream

    // Rectángulo desplazado para la sombra
    Rectangle {
        color: root.shadowColor
        height: root.height
        radius: root.radius
        visible: root.shadowEnabled && root.shadowOffset > 0
        width: root.width
        x: root.shadowOffset
        y: root.shadowOffset
        z: -1
    }
}
