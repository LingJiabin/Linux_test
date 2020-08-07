cmake_minimum_required(VERSION 2.8)

project(DEMO)

aux_source_directory(. DIR_SRCS)

add_subdirectory(lib)

add_executable(DEMO main.c)

target_link_libraries(DEMO SC crypto ssl pthread)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")