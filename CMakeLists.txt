cmake_minimum_required(VERSION 3.25)

project(
        8-track
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Dependencias
FetchContent_Declare(
        GoogleTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(GoogleTest)

enable_testing()
add_subdirectory(tests)

add_executable(main main.cpp)