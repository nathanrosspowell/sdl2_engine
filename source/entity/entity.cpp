//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS include.
#include "entity.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "../game/hopper.h"
#include "../yaml_helpers/doc.h"
#include "../log/log.h"
#include "../entity/entity.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STL includes.
#include <fstream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace entity
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Entity::Entity( game::Hopper& hopper, const String& yamlFile )
    : m_componentManager( hopper.getComponentMan() )
    , m_id( hopper.getEntityIdFactory().getNewIdentity() )
{
    stateStd( "Construct " << yamlFile );
    yaml_helpers::readDoc( yamlFile, 
        [&hopper,this]( const YAML::Node& doc )
        {
            auto& componentFactory = hopper.getComponentFactory();
            for ( auto& node : doc )
            {
                String name;
                node[ "name" ] >> name;
                componentFactory.make( name, hopper, node, *this );
            }
        });
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Entity::Entity( const Entity&& rhs )
    : m_componentManager( rhs.m_componentManager )
    , m_id( std::move( rhs.m_id ) )
    , m_myComponents( rhs.m_myComponents )
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Entity::doSetup( factory::SetupNode node
    , const String& classKey
    , Shared< factory::ISetup>&& newSetup )
{
    newSetup->doSetup( node );
    for ( auto& i : m_myComponents )
    {
        i->added( classKey, newSetup.get() );
        newSetup->added( i->classKey(), &(*i) );
    }
    m_myComponents.push_back( std::move( newSetup ) );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace entity
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~