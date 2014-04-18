//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "application.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STL includes.
#include <iostream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
#include "SDL_image.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local includes.
#include "renderer.h"
#include "../log/log.h"
#include "../command_line/auto_close_timer.h"
#include "../command_line/screen_dimensions.h"
#include "../component/render.h"
#include "../factory/factory.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Application::Application( const commandLine::CmdLine& cmdLine )
: m_hopper( cmdLine )
, m_state( State::Created )
, m_window( nullptr )
, m_renderer( nullptr )
{
    startUp();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Application::update()
{
    while ( true )
    {
        switch ( m_state )
        {
        case State::Loading:
            {
                if ( finishedLoading() )
                {
                    m_state = State::Running;
                }
            }
            break;
        case State::Running:
            {
                running();
            }
            break;
        case State::ShuttingDown:
            {
                if ( finishedShuttingDown() )
                {
                    m_state = State::Finished;
                }
            }
            break;
        case State::Finished:
            {
                return;
            }
            break;
        default: break;
        }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Application::startUp()
{
    stateStd( "" );
    m_state = State::Loading;
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 )
    {
        const auto& cmdLine = m_hopper.getCmdLine();
        auto screen = cmdLine.get< commandLine::ScreenDimensions >();
        int screenWidth = screen.getScreenWidth();
        int screenHeigth = screen.getScreenHeight();

        m_window = SDL_CreateWindow( "SDL2"
            , 10
            , 10
            , screenWidth
            , screenHeigth
            , SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
        if ( m_window )
        {
            m_renderer = new Renderer( m_hopper, m_window );
            m_renderer->initalise();
        }
        else
        {
            errorStd( "SDL_CreateWindow Error: " << SDL_GetError() );
        }
    }
    else
    {
        errorStd( "SDL_Init Error: " << SDL_GetError() );
    }
    if ( m_renderer == nullptr )
    {
        shutDown();
    }
    // Game play tests
    auto& entityIdFactory = m_hopper.getEntityIdFactory();
    auto& componentMan = m_hopper.getComponentMan();
    m_entityId = entityIdFactory.getNewIdentity();
    {
        factory::JsonData data = nullptr;
        auto name = component::Render::getRegistrtyName();
        factory::Factory::get( name, m_hopper, data, m_entityId );
    }
    {
        auto myComp = componentMan.get<component::Render>( m_entityId );
        if ( !myComp )
        {
            errorStd( "Couldn't get component::Render!!!1111111111111111111");
        }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Application::shutDown()
{
    stateStd( "" );
    m_state = State::ShuttingDown;
    m_renderer->shutDown();
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Application::finishedLoading()
{
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Application::running()
{
    m_hopper.update( 0 );
    m_renderer->update();
    // Remove debug...
    const auto& cmdLine = m_hopper.getCmdLine();
    auto closeTimer = cmdLine.get< commandLine::AutoCloseTimer >();
    if ( closeTimer.hasSetAutoCloseTimer() && 
         SDL_GetTicks() > closeTimer.getAutoCloseTimer() )
    {
        shutDown();
    }
    else if ( m_renderer->userQuit() )
    {
        shutDown();
    }

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Application::finishedShuttingDown()
{
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{}[]