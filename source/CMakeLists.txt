#################################################################
cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
set (CMAKE_VERBOSE_MAKEFILE ON)

set (App_Name "sdl2_engine")
if(App_Name STREQUAL "")
	message(FATAL_ERROR "You Must set the App_Name varable")
endif()

project (${App_Name})

set( ${App_Name}_VERSION_MAJOR 0 )
set( ${App_Name}_VERSION_MINOR 1 )

set( CMAKE_MODULE_PATH 
     ${CMAKE_MODULE_PATH} 
     "${CMAKE_SOURCE_DIR}/../cmake/"
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set( 
    CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11"
)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# All the source listing files for the component folder. 
file( GLOB LadderSource "ladder/source_listing/listing_*.cpp" )
file( GLOB ComponentSource "component/source_listing/listing_*.cpp" )
file( GLOB PassportSource "passport/source_listing/listing_*.cpp" )
file( GLOB EntitySource "entity/source_listing/listing_*.cpp" )
file( GLOB CommandLineSource "command_line/source_listing/listing_*.cpp" )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Set all the sources.
set(
   SOURCES
   "${CMAKE_SOURCE_DIR}/sdl2_engine.cpp"
   ${LadderSource}
   ${ComponentSource}
   ${EntitySource}
   ${PassportSource}
   ${CommandLineSource}
)

link_directories(
)

include_directories(
	${CMAKE_SOURCE_DIR}/include
)


#################################################################3
find_package(SDL2)
if (NOT SDL2_FOUND)
	message (FATAL_ERROR "SDL not found!")
endif (NOT SDL2_FOUND)

find_package(SDL2_image)
if (NOT SDL2IMAGE_FOUND)
	message (FATAL_ERROR "SDL_Image not found!")
endif (NOT SDL2IMAGE_FOUND)

find_package(SDL2_ttf)
if (NOT SDL2TTF_FOUND)
	message (FATAL_ERROR "SDL_ttf not found!")
endif (NOT SDL2TTF_FOUND)

find_package(SDL2_mixer)
if (NOT SDL2MIXER_FOUND)
	message (FATAL_ERROR "SDL_mixer not found!")
endif (NOT SDL2MIXER_FOUND)

include_directories(
	${SDL2_INCLUDE_DIR}
	${INCLUDE_DIRECTORIES}
)

# Final executable.
add_executable(
   ${App_Name}
   #WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
   #MACOSX_BUNDLE
   ${SOURCES} # We could've listed the source files here directly instead of using a variable to store them
)

target_link_libraries(
    ${App_Name}
	${SDL2_LIBRARY}
	${SDL2MAIN_LIBRARY}
	${SDL2IMAGE_LIBRARY}
	${SDL2MIXER_LIBRARY}
	${SDL2MAIN_LIBRARY}
	${SDL2IMAGE_LIBRARY}
	${SDL2TTF_LIBRARY}
	${TARGET_LINK_LIBRARIES}
)



