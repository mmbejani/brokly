cmake_minimum_required(VERSION 3.12)

project(Brokly VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB function_src src/function/*.cc)
file(GLOB tensor src/tensor/*.cc)

file(GLOB tensor/header)

add_library(mylib
    src/test.cpp          # Implementation
    include/test.hh    
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