//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../camera/manager.h"
#include "../component/manager.h"
#include "../render/manager.h"
#include "../passport/identity_factory.h"
#include "../passport/passport.h"
#include "../entity/entity.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
    class CmdLine;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Hopper
{
public:
    friend class Application;
    using EntityIdFactory = passport::IdentityFactory< entity::Entity >;
// Variables
public:
protected:
private:
    const commandLine::CmdLine& m_cmdLine;
    // Managers
    camera::Manager m_cameraMan;
    component::Manager m_componentMan;
    render::Manager m_renderMan;
    // Factories
    EntityIdFactory m_entityIdFactory;
// Functions
public:
    explicit Hopper( const commandLine::CmdLine& arguments );
    const commandLine::CmdLine& getCmdLine() const { return m_cmdLine; }
    camera::Manager& getCameraMan() { return m_cameraMan; }
    component::Manager& getComponentMan() { return m_componentMan; }
    render::Manager& getRenderMan() { return m_renderMan; }
    EntityIdFactory& getEntityIdFactory() { return m_entityIdFactory; }
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
