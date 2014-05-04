//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/location.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local inlcudes.
#include "base.h"
#include "component_list.h"
#include "../types/stl.hxx"
#include "../types/glm.hxx"
#include "../factory/types.hxx"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace component
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Location : public Base
{
// Variables
public:
protected:
private:
    Vec3 m_position;
    Vec3 m_rotation;
// Functions
public:
    virtual ~Location();
    Location( game::Hopper& hop, const entity::Id& id );
    static String getRegistrtyName() { return String( "location" ); }
    Vec3 getPos() const { return m_position; }
protected:
private:
    Location() = delete;
    Location( Location& ) = delete;
    Location( Location&& ) = delete;
    Location& operator = ( Location & ) = delete;
    Location& operator = ( Location && ) = delete;
    friend class ComponentList< Location >;
    virtual String classKey() const override { return getRegistrtyName(); }
    virtual void doSetup( factory::SetupNode node ) override;
    virtual void added( const String& name, factory::ISetup* added ) override;
    virtual void deleted( const String& name, factory::ISetup* deleted ) override;
    void update( int frameDelta );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
