cmake_minimum_required(VERSION 3.25)

project(
        eight-track
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql)
qt_standard_project_setup(REQUIRES 6.5)
qt_policy(SET QTP0004 NEW)
set(QT_QML_GENERATE_QMLLS_INI ON)

include(FetchContent)

# Dependencias
FetchContent_Declare(
        GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)

FetchContent_Declare(
        Taglib
        GIT_REPOSITORY https://github.com/taglib/taglib
        GIT_TAG v2.3.2
)

FetchContent_Declare(
        argparse
        GIT_REPOSITORY https://github.com/p-ranav/argparse
        GIT_TAG v3.2
)

FetchContent_Declare(
        tabulate
        GIT_REPOSITORY https://github.com/p-ranav/tabulate
        GIT_TAG v2.0
)

FetchContent_MakeAvailable(GoogleTest Taglib argparse tabulate)

target_include_directories(tag INTERFACE
        $<BUILD_INTERFACE:${taglib_SOURCE_DIR}>
        $<BUILD_INTERFACE:${taglib_SOURCE_DIR}/taglib>
        $<BUILD_INTERFACE:${taglib_SOURCE_DIR}/taglib/toolkit>
        $<BUILD_INTERFACE:${taglib_BINARY_DIR}>
)

add_subdirectory(8-track)

enable_testing()
add_subdirectory(tests)

# CLI
add_executable(track8-cli 8-track/src/cli/main.cpp)
target_link_libraries(track8-cli PRIVATE compiler miner database services cli)

# GUI
add_executable(track8 8-track/src/gui/main.cpp)

qt_add_qml_module(track8
        URI Track8
        VERSION 1.0
        QML_FILES
        8-track/qml/Main.qml
)

target_link_libraries(track8 PRIVATE Qt6::Quick compiler miner database services)