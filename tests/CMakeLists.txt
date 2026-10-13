add_executable(tests
    domain/test_date.cpp
)

target_link_libraries(tests
        PRIVATE
        GTest::gtest_main
        domain
)

include(GoogleTest)
gtest_discover_tests(tests)