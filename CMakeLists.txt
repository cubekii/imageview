cmake_minimum_required(VERSION 3.16)
project(imageview)

set(CMAKE_CXX_STANDARD 20)

if (PROJECT_IS_TOP_LEVEL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif ()

file(DOWNLOAD
        https://raw.githubusercontent.com/aui-framework/aui/df77317f6d1d8a08bd6d0f6e4b36a75e6037afea/aui.boot.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/aui.boot.cmake)

auib_import(SDL3 https://github.com/libsdl-org/SDL
        VERSION c20a058ff431d046c5806bd22aba0835b25d9904)
auib_import(SDL3_image https://github.com/libsdl-org/SDL_image
        VERSION fcb9d0b15f6bc4e22e9badedc5cdccee92eddcf4)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
add_executable(imageview ${SOURCES})

if(WIN32)
    set_target_properties(imageview PROPERTIES
        WIN32_EXECUTABLE TRUE)
endif()

target_link_libraries(imageview PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)
target_include_directories(imageview PRIVATE src)