cmake_minimum_required(VERSION 3.16)
project(libsdl3-examples C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The example sources use the SDL2 API (#include <SDL2/SDL.h>).
find_package(SDL2 REQUIRED)

# Each example is fully self-contained in src/<app>/<app>.c.
#   maze       : tile/BMP maze game (needs assets/)
#   animation  : two animated translucent rectangles
#   colorbars  : cycling color bars with a quit button
foreach(app maze animation colorbars)
  add_executable(${app} src/${app}/${app}.c)
  target_link_libraries(${app} PRIVATE SDL2::SDL2)
endforeach()
