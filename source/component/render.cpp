
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/manager.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS include.
#include "render.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local includes.
#include "../render/item.h"
#include "../game/hopper.h"
#include "../log/log.h"
#include "../gl_helpers/primitives.h"
#include "../yaml_helpers/stream.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace component
{
Render::~Render()
{
    stateStd( "Destroy:" << this );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Render::Render( game::Hopper& hop, const entity::Id& id )
    : Base( hop, id )
    , m_item( hop.getRenderMan().makeItem() )
    , m_location( nullptr )
    , m_type( 0 )
{
    stateStd( "Create" << this );

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*virtual*/void Render::doSetup( factory::SetupNode node )
{
    const auto* typeNode = node.FindValue("type");
    if( typeNode )
    {
        *typeNode >> m_type;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*virtual*/ void Render::added( const String& name, ISetup* added )
{
    stateStd( name << " to " << this );
    if ( name.compare( Location::getRegistrtyName() ) == 0 )
    {
        m_location = static_cast< Location* >( added );
        if( m_location )
        {
            addItem();
        }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*virtual*/ void Render::deleted( const String& name, ISetup* /*deleted*/ )
{
    stateStd( name << " from " << this );
    if ( name.compare( Location::getRegistrtyName() ) == 0 )
    {
        m_location = nullptr;
        m_item = nullptr;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Render::update( int /*frameDelta*/ )
{
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Render::addItem()
{
    switch ( m_type )
    {
    case 100:
        m_item->setPolygons( 
            [this]()
            {
                if ( m_location )
                {
                    gl_helpers::primitives::axisArrow( 0.2f, m_location->getPos() );
                }
            } );
        break;
    default:
        m_item->setPolygons( 
            [this]()
            {
                if ( m_location )
                {
                    gl_helpers::primitives::cube( 0.5f, m_location->getPos() );
                }
            } );
        break;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespave component
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~