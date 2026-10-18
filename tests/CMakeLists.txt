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
)

target_link_libraries(database_tests
    PRIVATE
        GTest::gtest
        domain
        database
        Qt6::Core
)

include(GoogleTest)
gtest_discover_tests(domain_tests)
gtest_discover_tests(miner_tests)
gtest_discover_tests(database_tests)