//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sdl2_engine.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <iostream>
#include <cstdint> 
#include <vector> 
#include <string>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
#include "SDL_image.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local
#include "command_line/base.h"
#include "game/application.h"
#include "log/log.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main( int argc, const char* const argv[])
{
    stateStd( "Main start: " << SDL_GetTicks() );
    // Create the arguments class
    std::vector< std::string > arguments;
    for ( int i = 0; i < argc; ++i )
    {
        arguments.push_back( argv[ i ] );
    }
    commandLine::Base cmdLine( arguments );
    // Create the application.
    game::Application application( cmdLine );
    application.update();

    stateStd( "Main end: " << SDL_GetTicks() );
    return 0;
}
