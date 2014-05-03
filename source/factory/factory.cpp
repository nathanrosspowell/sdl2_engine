//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "factory.h"
#include "../game/hopper.h"
#include "../log/log.h"
#include "../entity/entity.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace factory
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Factory::add( const String& classKey, AddFunc factoryFunc )
{
    std::pair< String, AddFunc > pair( classKey, factoryFunc );
    m_functionMap.insert( pair );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Factory::remove( const String& classKey )
{
    m_functionMap.erase( classKey );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Factory::make( const String& classKey
    , game::Hopper& hop
    , SetupNode node
    , entity::Entity& entity )
{
    stateStd( classKey );
    auto funcIt = m_functionMap.find( classKey );
    if ( funcIt != m_functionMap.end() )
    {
        const auto& addFunc = funcIt->second;
        entity.doSetup( node, classKey, addFunc( hop, entity.getIdentity() ) );
    }
    else
    {
        errorStd( "Could not find " << classKey );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace factory.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~