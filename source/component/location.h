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
#include "../entity/entity.h"
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
    
// Functions
public:
    Location( game::Hopper& hop, const entity::Id& id );
    Location( Location& ) = default;
    Location( Location&& ) = default;
    Location& operator = ( Location && ) = default;
    static String getRegistrtyName() { return String( "location" ); }
protected:
private:
    Location() = delete;
    friend class ComponentList< Location >;
    virtual String classKey() const override { return getRegistrtyName(); }
    virtual void doSetup( factory::JsonData json ) override;
    virtual void added( const String& name, ISetup* added ) override;
    virtual void deleted( const String& name, ISetup* deleted ) override;
    void update( int frameDelta );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~