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

set( CMAKE_USE_RELATIVE_PATHS ON )

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set( MAKE_C_COMPILER clang )
set( CMAKE_CXX_COMPILER clang++ )

set( 
    CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Werror"
)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# All the source listing files for the component folder. 
file( GLOB LocalSource "${CMAKE_SOURCE_DIR}/*/source_listing/listing_*.cpp" )

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Set all the sources.
set(
   SOURCES
   "${CMAKE_SOURCE_DIR}/sdl2_engine.cpp"
   ${LocalSource}
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

find_package(GL)
if (NOT HAVE_GL)
    message (FATAL_ERROR "GL not found!")
endif (NOT HAVE_GL)

find_package(GLU)
if (NOT HAVE_GLU)
    message (FATAL_ERROR "GLU not found!")
endif (NOT HAVE_GLU)

find_package(GLEW)
if (NOT HAVE_GLEW)
    message (FATAL_ERROR "GLEW not found!")
endif (NOT HAVE_GLEW)

find_package(GLM)
if (NOT GLM_FOUND)
    message (FATAL_ERROR "GLM not found!")
endif (NOT GLM_FOUND)

find_package(CPPCONFIG)
if (NOT CPPCONFIG_FOUND)
    message (FATAL_ERROR "CPPCONFIG not found!")
endif (NOT CPPCONFIG_FOUND)


include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIR}
    ${INCLUDE_DIRECTORIES}
    ${GL_INCLUDE_DIR}
    ${GLU_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${CPPCONFIG_INCLUDE_DIRS}
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
    GL
    ${GL_LIBRARIES}
    ${GLU_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SDL2_LIBRARY}
    ${SDL2MAIN_LIBRARY}
    ${SDL2IMAGE_LIBRARY}
    ${SDL2MIXER_LIBRARY}
    ${SDL2MAIN_LIBRARY}
    ${SDL2IMAGE_LIBRARY}
    ${SDL2TTF_LIBRARY}
    ${TARGET_LINK_LIBRARIES}
)


get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()


