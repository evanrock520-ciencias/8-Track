import QtQuick
import Track8

Item {
    id: root

    readonly property var pages: ({
            albums: albumsPage,
            artists: artistsPage,
            songs: songsPage,
            search: searchPage
        })
    property string section: "albums"

    Loader {
        anchors.fill: parent
        sourceComponent: root.pages[root.section] ?? root.pages.albums
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
        id: searchPage

        SearchPage {}
    }
}
