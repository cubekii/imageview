cmake_minimum_required(VERSION 4.3)
project(imageview)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
add_executable(imageview ${SOURCES})

target_link_libraries(imageview PRIVATE
        sdl::sdl
        SDL3_image::SDL3_image
)
target_include_directories(imageview PRIVATE src)