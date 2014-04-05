//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "base.h"
// Log.
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Base::Base( const std::vector< std::string >& arguments )
: m_screenWidth( SCREEN_WIDTH )
, m_screenHeight( SCREEN_HEIGHT )
, m_autoCloseTimer( 300 )
{
    parse( arguments );
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
#define testCase( CMD, FUNC ) \
    else if ( name.compare( CMD ) == 0 ) \
    {   FUNC( arguments );   }

    if ( name.empty() )
    {
        errorStd( "WHAT?" );
    }
    testCase( "screenDimensions", setScreenDimensions )
    testCase( "autoCloseTimer", setAutoCloseTimer )
    else
    {
        errorStd( "No match for " << name );
    }
#undef testCase
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Base::setScreenDimensions( const Strings& arguments )
{
    if ( arguments.size() == 2 )
    {
        std::istringstream width( arguments[ 0 ] );
        width >> m_screenWidth;
        std::istringstream height( arguments[ 1 ] );
        height >> m_screenHeight;
        stateStd( "New Dimensions: " << m_screenWidth << "x" << m_screenHeight );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Base::setAutoCloseTimer( const Strings& arguments )
{
    if ( arguments.size() == 1 )
    {
        std::istringstream timer( arguments[ 0 ] );
        timer >> m_autoCloseTimer;
        stateStd( "New auto close timer: " << m_autoCloseTimer );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace commandLine
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~