# Test de entidades de dominio.
add_executable(domain_tests
    domain/test_date.cpp
)

target_link_libraries(domain_tests
        PRIVATE
        GTest::gtest_main
        domain
)

# Test del minero.
add_executable(miner_tests
        miner/test_miner.cpp
)

target_compile_definitions(miner_tests
        PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data"
)

target_link_libraries(miner_tests
    PRIVATE
        GTest::gtest_main
        tag
        domain
        miner
)

# Test de la base de datos.
add_executable(database_tests
        database/main.cpp
        database/test_album_repository.cpp
        database/test_performer_repository.cpp
        database/test_song_repository.cpp
)

target_link_libraries(database_tests
    PRIVATE
        GTest::gtest
        domain
        database
        Qt6::Core
)

# Test de la capa de servicios
add_executable(services_tests
        services/main.cpp
        services/test_library_service.cpp
)

target_link_libraries(services_tests
    PRIVATE
        GTest::gtest
        domain
        database
        miner
        services
        Qt6::Core
)

# Test del compilador MuQL
add_executable(compiler_tests
    compiler/test_lexer.cpp
        compiler/test_ast.cpp
        compiler/test_parser.cpp
)

target_link_libraries(compiler_tests
    PRIVATE
        GTest::gtest_main
        compiler
)

include(GoogleTest)
gtest_discover_tests(domain_tests)
gtest_discover_tests(miner_tests)
gtest_discover_tests(database_tests)
gtest_discover_tests(services_tests)
gtest_discover_tests(compiler_tests)