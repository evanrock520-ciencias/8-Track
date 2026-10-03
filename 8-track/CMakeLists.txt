add_library(compiler
    src/compiler/Token.cpp
)

target_include_directories(compiler PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)