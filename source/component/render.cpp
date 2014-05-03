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
{
    stateStd( "Create" << this );

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Render::Render( Render&& rhs )
    : Base( std::move( rhs ) )
    , m_item( rhs.m_item )
    , m_location( rhs.m_location )
{
    stateStd( "Move construct " << this );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*virtual*/void Render::doSetup( factory::SetupNode /*node*/ )
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*virtual*/ void Render::added( const String& name, ISetup* added )
{
    stateStd( name << " to " << this );
    if ( name.compare( Location::getRegistrtyName() ) == 0 )
    {
        m_location = static_cast< Location* >( added );
        if ( m_location )
        {
            m_item->setPolygons( 
                [this]()
                {
                    if ( m_location )
                    {
                        gl_helpers::primitives::cube( 0.5f, m_location->getPos() );
                    }
                } );
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
// End namespave component
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~