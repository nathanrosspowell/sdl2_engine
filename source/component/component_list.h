
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
    Vector< T > m_components;
// Functions
public:
    ComponentList( factory::Factory& fact )
        : m_registry( fact, T::getRegistrtyName()
            , [this]( game::Hopper& hop, const entity::Id& id )
            {
                m_components.emplace_back( Component( hop, id ) );
                return makeShared( m_components.back() );
            } )
    {}
    void update( int frameDelta )
    {
        for ( auto& c : m_components )
        {
            c.update( frameDelta );
        }
    }
    const Vector< T >& getComponents() const { return m_components; };
    Vector< T >& getComponentsForEdit() { return m_components; };
    U32 size() const { return m_components.size(); }
protected:
private:
    Shared< factory::ISetup > makeShared( T& comp )
    {
        factory::ISetup* item = static_cast<factory::ISetup*>( &comp );
        return Shared< factory::ISetup >( item, [this]( factory::ISetup* setup )
            {
                auto compo = static_cast<T*>( setup );
                auto iter = std::find( m_components.begin(), m_components.end(), *compo );
                if ( iter != m_components.end() )
                {
                     m_components.erase( iter );
                }
            });
    }
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
