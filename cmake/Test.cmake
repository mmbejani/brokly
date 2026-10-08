if (BUILD_TEST)
    find_package(GTest REQUIRED PATHS /opt/gtest)

    include_directories(/opt/gtest/include)

    file(GLOB_RECURSE TEST_SOURCES tests/memory_test.cpp)

    enable_testing()

    add_executable(test_brokly ${TEST_SOURCES})

    target_link_libraries(test_brokly GTest::gtest_main brokly)
endif()