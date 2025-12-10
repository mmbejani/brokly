cmake_minimum_required(VERSION 3.20)

project(Brokly VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(src)
include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS 
    src/*.cpp
    src/*.hpp 
    src/*.c
    src/*.h
    include/*.hpp
    include/*.h)


add_library(brokly SHARED
    ${SOURCES}
)