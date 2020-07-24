cmake_minimum_required(VERSION 2.8)

project(Demo)

aux_source_directory(. DIR_SRCS)

add_subdirectory(lib)

add_executable(Demo main.cc)

target_link_libraries(Demo SMIME crypto)

