//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sdl2_engine.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <vector> 
#include <string>
#include <fstream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local
#include "command_line/cmd_line.h"
#include "game/application.h"
#include "log/log.h"

#include "yaml-cpp/yaml.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main( int argc, const char* const argv[])
{
    
    std::fstream fin( "../resources/yaml/config.yaml" );
    YAML::Parser parser( fin );
    YAML::Node doc;
    while ( parser.GetNextDocument(doc) )
    {
        for ( auto& x : doc )
        {
            int val = 0;
            x >> val;
            stateStd( "YAML " << val );
        }
    }


    stateStd( "Main start: " << SDL_GetTicks() );
    Strings arguments;
    for ( int i = 0; i < argc; ++i )
    {
        arguments.push_back( argv[ i ] );
    }
    commandLine::CmdLine cmdLine( arguments );
    stateStd( "Create application: " << SDL_GetTicks() );
    game::Application application( cmdLine );
    application.update();
    stateStd( "Main end: " << SDL_GetTicks() );
    return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
