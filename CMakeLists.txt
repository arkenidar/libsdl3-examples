cmake_minimum_required(VERSION 3.16)
project(libsdl3-examples C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The maze sources use the SDL2 API (#include <SDL2/SDL.h>).
find_package(SDL2 REQUIRED)

add_executable(maze src/maze/maze.c)
target_link_libraries(maze PRIVATE SDL2::SDL2)
