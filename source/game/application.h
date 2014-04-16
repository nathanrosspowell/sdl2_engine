//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../command_line/cmd_line.h"
#include "../camera/manager.h"
#include "../component/manager.h"
#include "../passport/identity_factory.h"
#include "../passport/passport.h"
#include "../entity/entity.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class SDL_Window;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Renderer;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Application
{
public:
    enum class State
    {
        Created,
        Loading,
        Running,
        ShuttingDown,
        Finished,
    };
protected:
private:
// Variables
public:
protected:
private:
    const commandLine::CmdLine m_cmdLine;
    State m_state;
    SDL_Window* m_window;
    Renderer* m_renderer;
    // Managers
    camera::Manager m_camera;
    component::Manager m_componentMan;
    // Factories
    passport::IdentityFactory< entity::Entity > m_entityIdFactory;
    entity::Id m_entityPassport;
// Functions
public:
     explicit Application( const commandLine::CmdLine& arguments );
     void update();
protected:
private:
    void startUp();
    void shutDown();
    bool finishedLoading();
    void running();
    bool finishedShuttingDown();
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
