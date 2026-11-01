import QtQuick
import Track8

Item {
    id: root

    readonly property var pages: ({
            overview: overviewPage,
            albums: albumsPage,
            artists: artistsPage,
            songs: songsPage,
            genres: genresPage,
            bands: placeholderPage,
            people: placeholderPage,
            unknown: placeholderPage
        })
    property string section: "overview"

    Loader {
        anchors.fill: parent
        sourceComponent: root.pages[root.section] ?? root.pages.overview
    }
    Component {
        id: overviewPage

        OverviewPage {}
    }
    Component {
        id: albumsPage

        AlbumsPage {}
    }
    Component {
        id: artistsPage

        ArtistsPage {}
    }
    Component {
        id: songsPage

        SongsPage {}
    }
    Component {
        id: genresPage

        GenresPage {}
    }
    Component {
        id: placeholderPage

        Item {
            Text {
                anchors.centerIn: parent
                color: Theme.grey
                font.family: Theme.fontFamily
                font.pixelSize: Theme.navBarItemFontSize
                text: "Unavailable Page"
            }
        }
    }
}
