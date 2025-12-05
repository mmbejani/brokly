cmake_minimum_required(VERSION 3.12)

project(Brokly VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c src/*.h)

include_directories(include)

add_library(brokly SHARED
    ${SOURCES}
)

# Include directories
target_include_directories(brokly
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(brokly PROPERTIES C_STANDARD 23)

# Install the library and headers (optional)
install(
    TARGETS brokly
    EXPORT brokly-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)