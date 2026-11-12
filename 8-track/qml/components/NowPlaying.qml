import QtQuick
import QtQuick.Layouts
import Track8

Item {
    id: root

    property url cover
    property string subtitle
    property string title

    implicitWidth: Theme.nowPlayingWidth

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: parent.top
        color: Theme.grey
        width: Theme.playbarBorderWidth
    }
    RowLayout {
        anchors.fill: parent
        anchors.margins: Theme.nowPlayingPadding
        spacing: Theme.nowPlayingSpacing

        Rectangle {
            Layout.preferredHeight: Theme.nowPlayingCoverSize
            Layout.preferredWidth: Theme.nowPlayingCoverSize
            color: Theme.cream

            Image {
                anchors.fill: parent
                anchors.margins: Theme.borderWidth
                asynchronous: true
                fillMode: Image.PreserveAspectCrop
                mipmap: true
                source: root.cover
                sourceSize.width: width * Screen.devicePixelRatio
                sourceSize.height: height * Screen.devicePixelRatio
            }
        }
        ColumnLayout {
            Layout.fillWidth: true
            spacing: 4

            Tag {
                text: "NOW PLAYING"
            }

            Text {
                Layout.fillWidth: true
                color: Theme.cream
                elide: Text.ElideRight
                font.family: Theme.fontFamily
                font.pixelSize: Theme.nowPlayingTitleFontSize
                text: root.title
            }
            Text {
                Layout.fillWidth: true
                color: Theme.cream
                elide: Text.ElideRight
                font.family: Theme.fontFamily
                font.pixelSize: Theme.nowPlayingSubtitleFontSize
                text: root.subtitle
            }
        }
    }
}
