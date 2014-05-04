
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/manager.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STL includes.
#include <algorithm>
// Local includes.
#include "../types/stl.hxx"
#include "../types/int.hxx"
#include "../factory/factory.h"
#include "../factory/types.hxx"
#include "../factory/register.h"
#include "../entity/types.hxx"
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace component
{
template< class T >
class ComponentList
{
    using Component = T;
// Variables
public:
protected:
private:
    factory::Register m_registry;
    Vector< Component* > m_components;
// Functions
public:
    ComponentList( factory::Factory& fact )
        : m_registry( fact, T::getRegistrtyName()
            , [this]( game::Hopper& hop, const entity::Id& id )
            {
                return makeShared( hop, id );
            } )
    {}
    void update( int frameDelta )
    {
        for_each(m_components, [=](Component* c){c->update(frameDelta);});
    }
    const Vector< Component* >& getComponents() const { return m_components; };
    Vector< Component* >& getComponentsForEdit() { return m_components; };
    U32 size() const { return m_components.size(); }
protected:
private:
    Shared< factory::ISetup > makeShared( game::Hopper& hop, const entity::Id& id )
    {
        Component* item = new Component( hop, id );
        m_components.push_back( item );
        return Shared< factory::ISetup >( item, [this]( factory::ISetup* setup )
            {
                auto comp = static_cast<Component*>( setup );
                auto iter = std::find( m_components.begin(), m_components.end(), comp );
                m_components.erase( iter );
                delete( comp );
            });
    }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
