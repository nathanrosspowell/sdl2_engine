//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "entity.h"
#include "../game/hopper.h"
#include "../component/manager.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace entity
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Entity::Entity( game::Hopper& hopper, const String& )//yamlFile )
    : //m_componentManager( hopper.getComponentMan() )
     m_id( hopper.getEntityIdFactory().getNewIdentity() )
{
    /*
    {
        auto name = component::Render::getRegistrtyName();
        componentFactory.get( name, m_hopper, data, m_entityId );
    }
    {
        auto name = component::Location::getRegistrtyName();
        componentFactory.get( name, m_hopper, data, m_entityId );
    }


        yaml_helpers::Doc doc( "../resources/yaml/config.yaml" );
    for ( const auto& node : doc )
    {
        for ( const auto& number : *node )
        {
            int val;
            number >> val;
            stateStd( "YAML " << val );
        }
    }
*/
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace entity
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~