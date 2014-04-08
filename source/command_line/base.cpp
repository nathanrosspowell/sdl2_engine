//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "base.h"
// Standard library.
#include <algorithm> 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Log.
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ScreenDimensions::dispatch( const Strings& arguments )
{
    if ( arguments.size() == 2 )
    {
        std::istringstream width( arguments[ 0 ] );
        width >> m_screenWidth;
        std::istringstream height( arguments[ 1 ] );
        height >> m_screenHeight;
        stateStd( "New screen dimensions: " 
            << m_screenWidth 
            << "x" 
            << m_screenHeight );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void AutoCloseTimer::dispatch( const Strings& arguments )
{
    if ( arguments.size() == 1 )
    {
        std::istringstream timer( arguments[ 0 ] );
        timer >> m_autoCloseTimer;
        stateStd( "New auto close timer: " << m_autoCloseTimer );
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Base::Base( const std::vector< std::string >& arguments )
    : m_entries({
         new ScreenDimensions()
       , new AutoCloseTimer()
    } )
{
    parse( arguments );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Base::add( const std::string& name, IEntry* entry )
{
//    m_entries[ name ] = entry;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Base::parse( const Strings& arguments )
{
    const std::string seperator( "-" );
    std::string command;
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
                std::string cmd( command, 1 );
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
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Base::dispatch( const std::string& name, const Strings& arguments )
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
const IEntry& Base::find( const std::string& name ) const
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
IEntry* Base::find( const std::string& name )
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