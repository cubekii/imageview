cmake_minimum_required(VERSION 4.3)
project(imageview)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(imageview ${SOURCES})

target_link_libraries(imageview PRIVATE sdl::sdl)
target_include_directories(imageview PRIVATE src)