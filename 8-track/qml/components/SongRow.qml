import QtQuick
import QtQuick.Layouts
import Track8
import Track8.Backend 1.0

Item {
    id: root

    property string album
    property string artist
    property string title
    property int year
    property url path

    signal playClicked

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

        RowPlayButton {
            Layout.alignment: Qt.AlignVCenter
            onClicked: root.playClicked()
        }

        Text {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColTitleWidth
            color: Theme.ink
            elide: Text.ElideRight
            font.family: Theme.fontFamily
            font.pixelSize: Theme.songColTitleFontSize
            text: root.title
        }
        Text {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColArtistWidth
            color: Theme.grey
            elide: Text.ElideRight
            font.family: Theme.fontFamily
            font.pixelSize: Theme.songColSubtitlesFontSize
            font.weight: Font.Bold
            text: root.artist
        }
        Text {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColAlbumWidth
            color: Theme.grey
            elide: Text.ElideRight
            font.family: Theme.fontFamily
            font.pixelSize: Theme.songColSubtitlesFontSize
            text: root.album
        }
        Text {
            Layout.preferredWidth: Theme.songColYearWidth
            color: Theme.grey
            font.family: Theme.monoFontFamily
            font.pixelSize: Theme.songColSubtitlesFontSize
            text: root.year
        }
    }
}
