cmake_minimum_required(VERSION 3.20)

project(Brokly VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include(cmake/Definition.cmake)

include_directories(src)
include_directories(src/backend)
include_directories(include)

file(GLOB FUNCTI_SOURCE src/function/*.cpp)
file(GLOB MEMORY_SOURCE src/memory/*.hpp src/memory/*.cpp)
file(GLOB NEURAL_SOURCE src/nn/*.cpp)
#file(GLOB_RECURSE OPTIMA_SOURCE src/optim/*.cpp src/optim/*.hpp)
file(GLOB TENSOR_SOURCE src/tensor/*.cpp src/tensor/*.hpp)
file(GLOB UTILIT_SOURCE src/utils/*.cpp src/utils/*.hpp)

if (AMD)
message(STATUS "use avx as accelerator")
file(GLOB BACKEND_SOURCE src/backend/*.h src/backend/avx/*.c)
elseif(ARM)
message(STATUS "use neon as accelerator")
file(GLOB BACKEND_SOURCE src/backend/*.h src/backend/neon/*.c)
else()
message(STATUS "use non-accelerator")
file(GLOB BACKEND_SOURCE src/backend/*.h src/backend/direct/*.c)
endif()

add_library(brokly_backend STATIC ${BACKEND_SOURCE})

add_library(brokly SHARED
    ${FUNCTI_SOURCE} 
    ${MEMORY_SOURCE} 
    ${NEURAL_SOURCE} 
    ${TENSOR_SOURCE}
    ${UTILIT_SOURCE}
)

target_link_libraries(brokly PRIVATE brokly_backend)

include(cmake/Test.cmake)