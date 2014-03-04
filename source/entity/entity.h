//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once

#include "../passport/passport.h"
namespace entity
{
    class Entity
    {
    public:
    using IdentityType = unsigned int;
    using Id = passport::Passport< Entity >;
    // Variables
    public:
    protected:
    private:
        Id m_id;
    // Functions
        
    public:
        Entity();
    protected:
    private:
    };
}