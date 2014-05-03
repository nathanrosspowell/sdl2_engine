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
    stateStd( "Destroy Render::Manager" << m_nextId );
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
    m_items.push_back( Item( m_nextId++ ) );
    return makeShared( m_items.back() );
}
void Manager::update()
{
    for ( auto& i : m_items )
    {
        i.drawPolygons();
    }
}
Shared< Item > Manager::makeShared( Item& item )
{
    return Shared< Item >( &item,
        [this]( Item* item)
        {
            auto iter = std::find( m_items.begin(), m_items.end(), *item );
            if ( iter != m_items.end() )
            {
                 stateStd( "Shared< Item > Delete:Remove Item " << iter->getId() );
                 m_items.erase( iter );
            }
            else
            {
                stateStd( "Shared< Item > Delete: Item no longer there" );
            }
        });
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespave render.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~