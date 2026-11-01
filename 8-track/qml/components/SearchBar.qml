import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import Track8

NeobrutalistBox {
    id: root

    property string placeholder: "Search your library _"
    property alias text: field.text

    implicitHeight: Theme.searchBarHeight
    radius: Theme.searchBarRadius
    shadowEnabled: false

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.searchBarPaddingX + Theme.borderWidth
        anchors.rightMargin: Theme.searchBarPaddingX + Theme.borderWidth
        spacing: 8

        Image {
            Layout.alignment: Qt.AlignVCenter
            source: "qrc:/qt/qml/Track8/resources/icons/lens.svg"
            sourceSize: Qt.size(Theme.lensIconSize, Theme.lensIconSize)
        }
        TextField {
            id: field

            Layout.fillHeight: true
            Layout.fillWidth: true
            background: null
            color: Theme.ink
            font.family: Theme.monoFontFamily
            font.pixelSize: Theme.searchBarFontSize
            font.weight: Theme.searchBarWeight
            leftPadding: 0
            placeholderText: root.placeholder
            placeholderTextColor: Theme.grey
            verticalAlignment: TextInput.AlignVCenter
        }
    }
}
