cmake_minimum_required(VERSION 3.7)
project(NBodySolver)

set(CMAKE_CXX_STANDARD 11)

include_directories(include/)

file(GLOB SOURCE_FILES include/*.h source/*.cpp)

add_executable(NBodySolver ${SOURCE_FILES})