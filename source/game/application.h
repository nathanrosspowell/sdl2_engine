//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../command_line/cmd_line.h"

class SDL_Window;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{

class Renderer;

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

}