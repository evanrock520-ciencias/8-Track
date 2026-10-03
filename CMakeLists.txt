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

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include(FetchContent)

# Dependencias
FetchContent_Declare(
        GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(GoogleTest)

add_subdirectory(8-track)

enable_testing()
add_subdirectory(tests)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Qt6::Widgets compiler)