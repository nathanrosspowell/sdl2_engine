//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <iostream>
#include <sstream>

#define logError "ERROR"
#define logDebug "DEBUG"
#define logState "STATE"
#define logChannelStd "STD"

#define baseLog( SEVERITY, CHANNEL, FORMAT )\
{   std::ostringstream ss;\
    ss << "[" << SEVERITY \
       << "][" << CHANNEL \
       << "][" << __FILE__ \
       << "][" << __LINE__ \
       << __FUNCTION__ << "]" << FORMAT;\
    n_log::error( std::cout, ss.str() );}

#define errorLog( CHANNEL, FORMAT ) baseLog( logError, CHANNEL, FORMAT )
#define debugLog( CHANNEL, FORMAT ) baseLog( logDebug, CHANNEL, FORMAT )
#define stateLog( CHANNEL, FORMAT ) baseLog( logState, CHANNEL, FORMAT )

#define errorStd( FORMAT ) errorLog( logChannelStd, FORMAT )
#define stateStd( FORMAT ) stateLog( logChannelStd, FORMAT )
#define debugStd( FORMAT ) debugLog( logChannelStd, FORMAT )

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace n_log
{

void error( std::ostream &os, const std::string& stream );

}