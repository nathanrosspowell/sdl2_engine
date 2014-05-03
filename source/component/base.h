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
    Base( game::Hopper& hop, const entity::Id& id );
    Base( Base&& rhs )
    {
        m_hopper = rhs.m_hopper;
        m_entityId = rhs.m_entityId;
        m_componentId = std::move( rhs.m_componentId );
    }
    Base& operator = ( Base&& rhs )
    {
        m_hopper = rhs.m_hopper;
        m_entityId = rhs.m_entityId;
        m_componentId = std::move( rhs.m_componentId );
        return *this;
    }
    bool operator == ( const Base& rhs ) const
    {
        return this->m_componentId == rhs.m_componentId;
    }
    const entity::Id& getEntityId() const { return *m_entityId; }
    const Id& getComponentId() const { return m_componentId; }
protected:
    game::Hopper& getHopper() const { return *m_hopper; }
private:
    Base() = delete;
    game::Hopper* m_hopper;
    const entity::Id* m_entityId;
    Id m_componentId;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
