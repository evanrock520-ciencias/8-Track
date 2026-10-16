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
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/repositories/ISongRepository.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/domain/repositories/IPerformerRepository.hpp
)

# Biblioteca de Database
add_library(database
        src/database/DatabaseManager.cpp
        src/database/SQLiteAlbumRepository.cpp
        src/database/SQLitePerformerRepository.cpp
        src/database/SQLiteSongRepository.cpp
)

target_include_directories(database PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

qt_add_resources(database "schema"
    PREFIX "/sql"
        FILES resources/sql/rolas.sql
)

target_link_libraries(database PUBLIC Qt6::Sql Qt6::Core)

# Biblioteca de MuQL
add_library(compiler
    src/compiler/Token.cpp
)

target_include_directories(compiler PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Biblioteca del Minero
add_library(miner
    src/miner/Miner.cpp
)

target_include_directories(miner PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(miner PRIVATE tag)