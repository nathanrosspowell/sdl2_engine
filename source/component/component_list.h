//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/manager.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
// Functions
public:
    ComponentList()
        : m_registry( 
              T::getRegistrtyName()
            , [this]( factory::JsonData data, const entity::Id& id  )
            {
                Component item( id );
                item.doSetup( data );
                m_components.push_back( item );
                Component* itemPtr = &( m_components.back() );
                return static_cast< factory::ISetup* >( itemPtr );
            } 
        )
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
