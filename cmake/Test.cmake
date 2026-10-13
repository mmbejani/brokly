if (BUILD_TEST)
    find_package(GTest REQUIRED PATHS /opt/gtest)

    include_directories(/opt/gtest/include)

    enable_testing()
        
    add_executable(memory_test tests/memory_test.cpp include/memory/pool.hpp)

    target_link_libraries(memory_test GTest::gtest_main brokly)
endif()