import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8

ColumnLayout {
    id: root

    property string currentSection
    property var model: []
    property string title

    signal sectionSelected(string section)

    spacing: Theme.navSpacing

    Text {
        color: Theme.grey
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.navBarItemFontSize
        text: root.title
    }
    Repeater {
        model: root.model

        NavItem {
            active: root.currentSection === modelData.section
            Layout.fillWidth: true
            count: modelData.count
            icon.height: 16
            icon.source: "qrc:/qt/qml/Track8/resources/icons/" + modelData.icon + ".svg"
            icon.width: 16
            text: modelData.label

            onClicked: root.sectionSelected(modelData.section)
        }
    }
}
