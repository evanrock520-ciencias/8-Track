qt_policy(SET QTP0004 NEW)

set_source_files_properties(theme/Theme.qml
        PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module(track8
        URI Track8
        VERSION 1.0
        QML_FILES
        Main.qml
        theme/Theme.qml

        # Componentes
        components/Sidebar.qml
        components/Playbar.qml
        components/Topbar.qml
        components/Brand.qml

        RESOURCES
        resources/fonts/Inter-Variable.ttf
        resources/fonts/RobotoMono-Variable.ttf

        resources/icons/tape.svg
)