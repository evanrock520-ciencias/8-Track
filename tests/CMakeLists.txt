add_executable(domain_tests
    domain/test_date.cpp
)

target_link_libraries(domain_tests
        PRIVATE
        GTest::gtest_main
        domain
)

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

include(GoogleTest)
gtest_discover_tests(domain_tests miner_tests)