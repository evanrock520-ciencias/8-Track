add_executable(tests
    test_placeholder.cpp
)

target_link_libraries(tests
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)