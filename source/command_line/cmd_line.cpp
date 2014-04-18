//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "cmd_line.h"
// Standard library.
#include <algorithm> 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// command line.
#include "auto_close_timer.h"
#include "screen_dimensions.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Log.
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CmdLine::CmdLine( const std::vector< String >& arguments )
    : m_entries({
         new ScreenDimensions()
       , new AutoCloseTimer()
    } )
{
    parse( arguments );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
CmdLine::~CmdLine()
{
    // for ( auto entry : m_entries )
    // {
    //     if ( entry )
    //     {    stateStd( "Delete stuff " << entry->getCommandName() );
    //     delete entry;
    //     }else
    //      {   stateStd( "null wut?? " << entry );
    //     }
    // }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CmdLine::parse( const Strings& arguments )
{
    const String seperator( "-" );
    String command;
    Strings commandArgs;
    Strings copyArgs = arguments;
    copyArgs.push_back( "-" );
    for ( const auto& arg : copyArgs )
    {
        auto firstChar = arg.substr( 0, 1 );
        stateStd( arg << " " << firstChar );
        bool gotCommand = !command.empty();
        if ( firstChar == seperator )
        {
            if ( gotCommand )
            {
                String cmd( command, 1 );
                dispatch( cmd, commandArgs );
                commandArgs.clear();
            }
            command = arg;
        }
        else if ( gotCommand )
        {
            commandArgs.push_back( arg );
        }
    }
    stateStd( "DONE" );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CmdLine::dispatch( const String& name, const Strings& arguments )
{
    stateStd( name << " " << arguments.size() );
    if ( auto entry = find( name ) )
    {
        entry->dispatch( arguments );
    }
    else
    {
        errorStd( "No match for: " << name );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const IEntry& CmdLine::find( const String& name ) const
{
    auto iter = std::find_if( m_entries.begin(), m_entries.end(), 
        [name] ( const IEntry* entry )
        {
            return entry->getCommandName().compare( name ) == 0;
        } );
    SDL_assert( iter != m_entries.end() );
    return *(*iter);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
IEntry* CmdLine::find( const String& name )
{
    IEntry* entry = nullptr;
    auto iter = std::find_if( m_entries.begin(), m_entries.end(), 
        [name] ( const IEntry* entry )
        {
            return entry->getCommandName().compare( name ) == 0;
        } );
    if ( iter != m_entries.end() )
    {
        entry = *iter;
    }
    return entry;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace commandLine
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~