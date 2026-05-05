cmake_minimum_required(VERSION 4.3)
project(imageview)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)

add_executable(imageview src/main.cpp)

target_link_libraries(imageview PRIVATE sdl::sdl)