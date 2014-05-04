//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/manager.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS include.
#include "manager.h"
#include "../game/hopper.h"
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace component
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Manager::Manager( game::Hopper& hop )
    : m_renderComps( hop.getComponentFactory() )
    , m_locationComps( hop.getComponentFactory() )
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Manager::~Manager()
{
    stateStd( "Destroy component::Manager" );

    if ( m_renderComps.size() > 0 )
    {
        std::stringstream output;
        for( const auto& i : m_renderComps.getComponentsForEdit() )
        {
            auto address = static_cast<const void*>( &i );
            output << address;
            output << " ";
        }
        errorStd( "m_renderComps isn't empty: " <<  m_renderComps.size() << " - "<< output.str() );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Manager::update( int frameDelta )
{
    m_renderComps.update( frameDelta );
    m_locationComps.update( frameDelta );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Templates
template<> Render* Manager::get<Render>( const entity::Id& id )
{
    // optimize this stuff later.
    Render* retVal = nullptr;
    for ( auto& x : m_renderComps.getComponentsForEdit() )
    {
        if ( x->getEntityId() == id )
        {
            retVal = x;
            break;
        }
    }
    return retVal;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespave component
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~