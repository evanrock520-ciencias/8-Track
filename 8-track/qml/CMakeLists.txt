qt_policy(SET QTP0004 NEW)

qt_add_executable(track8 ../src/gui/main.cpp)

set_source_files_properties(theme/Theme.qml
        PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

set_source_files_properties(utils/Utils.qml
        PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(track8
        URI Track8
        VERSION 1.0
        QML_FILES
        Main.qml
        theme/Theme.qml
        utils/Utils.qml

        # Componentes
        components/Sidebar.qml
        components/Playbar.qml
        components/Topbar.qml
        components/Brand.qml
        components/StatusIndicator.qml
        components/NeobrutalistBox.qml
        components/NeobrutalistButton.qml
        components/SearchBar.qml
        components/NavItem.qml
        components/NavSection.qml
        components/NowPlaying.qml
        components/Tag.qml
        components/TrackControl.qml
        components/SimpleButton.qml
        components/StateButton.qml
        components/NeobrutalistSlider.qml
        components/PlaybackProgress.qml
        components/VolumeControl.qml
        components/OutputControls.qml
        components/ContentArea.qml
        components/SongRow.qml
        components/RowPlayButton.qml
        components/SongTableHeader.qml
        components/ScanModal.qml
        components/InfoBox.qml

        # Dialogs
        dialogs/DirectorySelector.qml

        # Pages
        pages/OverviewPage.qml
        pages/AlbumsPage.qml
        pages/ArtistsPage.qml
        pages/GenresPage.qml
        pages/SongsPage.qml

        RESOURCES
        resources/fonts/Inter-Variable.ttf
        resources/fonts/RobotoMono-Variable.ttf

        resources/icons/tape.svg
        resources/icons/scan.svg
        resources/icons/lens.svg
        resources/icons/cd.svg
        resources/icons/list-music.svg
        resources/icons/icons.svg
        resources/icons/microphone.svg
        resources/icons/artist.svg
        resources/icons/band.svg
        resources/icons/skip-back.svg
        resources/icons/skip-forward.svg
        resources/icons/shuffle.svg
        resources/icons/pause.svg
        resources/icons/play.svg
        resources/icons/volume.svg
        resources/icons/folder.svg

        resources/images/cover.png
)

target_link_libraries(track8 PRIVATE
        Qt6::Quick
        compiler
        miner
        database
        services
        gui
)
