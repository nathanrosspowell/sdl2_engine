//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// component/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "../factory/setup.h"
#include "../entity/entity_id.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
    class Hopper;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace component
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Base : public factory::ISetup
{
public:
    using IdentityType = unsigned int;
    using Id = passport::Passport< Base >;
// Variables
public:
protected:
private:
// Functions
public:
    virtual ~Base() = default;
    Base( game::Hopper& hop, const entity::Id& id );
    const entity::Id& getEntityId() const { return *m_entityId; }
    const Id& getComponentId() const { return m_componentId; }
protected:
    game::Hopper& getHopper() const { return *m_hopper; }
private:
    Base() = delete;
    Base( Base& rhs ) = delete;
    Base( Base&& rhs ) = delete;
    Base& operator = ( Base&& rhs )  = delete;
    bool operator == ( const Base& rhs ) const = delete;
    game::Hopper* m_hopper;
    const entity::Id* m_entityId;
    Id m_componentId;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
