//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../camera/manager.h"
#include "../component/manager.h"
#include "../component/base.h"
#include "../render/manager.h"
#include "../passport/identity_factory.h"
#include "../passport/passport.h"
#include "../entity/entity_id.h"
#include "../factory/factory.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine { class CmdLine; }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Hopper
{
public:
    friend class Application;
    using EntityIdFactory = passport::IdentityFactory< entity::EntityId >;
    using ComponentIdFactory = passport::IdentityFactory< component::Base >;
// Variables
public:
protected:
private:
    const commandLine::CmdLine& m_cmdLine;
    // Factories
    factory::Factory m_componentFactory;
    EntityIdFactory m_entityIdFactory;
    ComponentIdFactory m_componentIdFactory;
    // Managers
    camera::Manager m_cameraMan;
    component::Manager m_componentMan;
    render::Manager m_renderMan;
// Functions
public:
    explicit Hopper( const commandLine::CmdLine& arguments );
    const auto& getCmdLine() const { return m_cmdLine; }
    auto& getCameraMan() { return m_cameraMan; }
    auto& getComponentMan() { return m_componentMan; }
    auto& getRenderMan() { return m_renderMan; }
    auto& getEntityIdFactory() { return m_entityIdFactory; }
    auto& getComponentIdFactory() { return m_componentIdFactory; }
    auto& getComponentFactory() { return m_componentFactory; }
protected:
private:
    Hopper() = delete;
    Hopper( Hopper& ) = delete;
    void update( int frameDelta );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
