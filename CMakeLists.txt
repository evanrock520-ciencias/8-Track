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

add_executable(main 8-track/src/main.cpp)
target_link_libraries(main PRIVATE Qt6::Quick compiler argparse tabulate miner database)