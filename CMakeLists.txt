cmake_minimum_required(VERSION 3.7)
project(NBodySolver)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/implementations/)
include_directories(include/support/)
include_directories(include/)

file(GLOB SOURCE_FILES include/implementations/*.h include/support/*.h source/implementations/*.cpp source/support/*.cpp source/*.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++11 -Wno-deprecated-register")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

add_executable(NBodySolver ${SOURCE_FILES})