cmake_minimum_required(VERSION 3.28)
project(WALLSWAMP)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(WALLSWAMP ${SOURCES})
