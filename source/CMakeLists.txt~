#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# CMakeLists.txt Authored by Nathan Ross Powell.
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
 
PROJECT(sdl2_engine)
 
ADD_EXECUTABLE(sdl2_engine sdl2_engine.cpp)
 
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(sdl2_engine ${SDL2_LIBRARIES})
