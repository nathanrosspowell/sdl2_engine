//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/render.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local inlcudes.
#include "base.h"
#include "location.h"
#include "component_list.h"
#include "../types/stl.hxx"
#include "../factory/types.hxx"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace render
{
    class Item;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace component
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Render : public Base
{
// Variables
public:
protected:
private:
    Shared< render::Item > m_item;
    Location* m_location;
// Functions
public:
    virtual ~Render();
    Render( game::Hopper& hop, const entity::Id& id );
    static String getRegistrtyName() { return String( "render" ); }
protected:
private:
    Render() = delete;
    Render( Render& base ) = delete;
    Render& operator = ( Render & ) = delete;
    friend class ComponentList< Render >;
    virtual String classKey() const override { return getRegistrtyName(); }
    virtual void doSetup( factory::SetupNode node ) override;
    virtual void added( const String& name, factory::ISetup* added ) override;
    virtual void deleted( const String& name, factory::ISetup* deleted ) override;
    void update( int frameDelta );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
