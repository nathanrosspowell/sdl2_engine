//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// render/manager.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS include.
#include "manager.h"
#include <algorithm>
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace render
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Manager::Manager()
    : m_nextId( 0 )
{

}
Manager::~Manager()
{
    stateStd( "Destroy Render::Manager. m_nextId:" << m_nextId );
    if ( m_items.size() > 0 )
    {
        std::stringstream output;
        for( const auto& i : m_items )
        {
            auto address = static_cast<const void*>( &i );
            output << address;
            output << " ";
        }
        errorStd( "m_items isn't empty: " <<  m_items.size() << " - "<< output.str() );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Shared< Item > Manager::makeItem()
{
    stateStd( "Make Item " << m_nextId );
    Item* item = new Item( m_nextId++ );
    m_items.push_back( item );
    return Shared< Item >( item,
        [this]( Item* item)
        {
            auto iter = std::find( m_items.begin(), m_items.end(), item );
            m_items.erase( iter );
            delete( item );
        });
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Manager::update()
{
    for ( auto& i : m_items )
    {
        i->drawPolygons();
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespave render.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~