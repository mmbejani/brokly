cmake_minimum_required(VERSION 3.12)

project(Brokly VERSION 1.0 LANGUAGES C)

file(GLOB function_src src/function/*.c)
file(GLOB tensor src/tensor/*.c)

file(GLOB tensor/header)

add_executable(mylib
    src/test.c
    src/util/map.c
)

# Include directories
target_include_directories(mylib
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Install the library and headers (optional)
install(
    TARGETS mylib
    EXPORT mylib-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)