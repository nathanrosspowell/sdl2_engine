//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "factory.h"
#include "../game/hopper.h"
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace factory
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Factory::add( const String& classKey, Funcs funcs )
{
    std::pair< String, Funcs > pair( classKey, funcs );
    m_functionMap.insert( pair );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Factory::remove( const String& classKey )
{
    m_functionMap.erase( classKey );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
ISetup* Factory::get( const String& classKey
    , game::Hopper& hop
    , SetupNode node
    , const entity::Id& id )
{
    stateStd( classKey );
    ISetup* newSetup = nullptr;
    auto funcIt = m_functionMap.find( classKey );
    if ( funcIt != m_functionMap.end() )
    {
        newSetup = funcIt->second.Add( hop, id );
        if ( newSetup )
        {
            newSetup->doSetup( node );
            auto& otherSetupsForId = m_setupMap[ id.getIdentity() ];
            for ( auto* i : otherSetupsForId )
            {
                i->added( classKey, newSetup );
                newSetup->added( i->classKey(), i );
            }
            otherSetupsForId.push_back( newSetup );
        }
    }
    else
    {
        errorStd( "Could not find " << classKey );
    }
    return newSetup;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace factory.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~