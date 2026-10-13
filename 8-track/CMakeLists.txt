# Biblioteca de clases de dominio
add_library(domain INTERFACE)

target_include_directories(domain INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(domain INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/Song.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/Album.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/Performer.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/Artist.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/Group.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/Date.hpp

        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/repositories/IAlbumRepository.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/repositories/IAlbumRepository.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/repositories/IPerformerRepository.hpp
)

# Biblioteca de MuQL
add_library(compiler
    src/compiler/Token.cpp
)

target_include_directories(compiler PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)