import QtQuick
import QtQuick.Layouts
import Track8

Rectangle {
    id: root

    color: Theme.ink
    implicitHeight: Theme.songHeaderHeight

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: Theme.songRowPaddingX
        anchors.rightMargin: Theme.songRowPaddingX
        spacing: Theme.songRowSpacing

        HeaderLabel {
            Layout.preferredWidth: Theme.rowPlayButtonSize
            horizontalAlignment: Text.AlignHCenter
            text: "#"
        }
        HeaderLabel {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColTitleWidth
            text: "TITLE"
        }
        HeaderLabel {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColArtistWidth
            text: "ARTIST"
        }
        HeaderLabel {
            Layout.fillWidth: true
            Layout.preferredWidth: Theme.songColAlbumWidth
            text: "ALBUM"
        }
        HeaderLabel {
            Layout.preferredWidth: Theme.songColYearWidth
            text: "YEAR"
        }
    }

    component HeaderLabel: Text {
        color: Theme.cream
        elide: Text.ElideRight
        font.family: Theme.monoFontFamily
        font.pixelSize: Theme.songColTitleFontSize
        font.weight: Font.Bold
    }
}
