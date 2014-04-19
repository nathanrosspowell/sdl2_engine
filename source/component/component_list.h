//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/manager.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STL includes.
#include <algorithm>
// Local includes.
#include "../types/stl.hxx"
#include "../factory/factory.h"
#include "../factory/register.h"
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
    factory::Funcs m_funcs = 
    {
        [this]( game::Hopper& hop, const entity::Id& id )
        {
            m_components.push_back( Component( hop, id ) );
            Component* itemPtr = &( m_components.back() );
            return static_cast< factory::ISetup* >( itemPtr );
        }
        , [this]( game::Hopper& /*hop*/, factory::ISetup* deleted )
        {
             T* comp = static_cast< T* >( deleted );
             const auto& id = comp->getComponentId();
             auto iter = std::remove_if ( m_components.begin()
                , m_components.end()
                , [&]( const T& x ) { return x.getComponentId() == id; } );
             m_components.erase( iter, m_components.end() );
        }
    };
// Functions
public:
    ComponentList( factory::Factory& fact )
        : m_registry( fact, T::getRegistrtyName(), m_funcs )
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
protected:
private: 
    factory::Register m_registry;
    Vector< T > m_components;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
