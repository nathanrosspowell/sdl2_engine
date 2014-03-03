//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Application::Application( const commandLine::Base& cmdLine )
: m_cmdLine( cmdLine )
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
        m_window = SDL_CreateWindow( "SDL2"
            , 10
            , 10
            , m_cmdLine.GetScreenWidth()
            , m_cmdLine.GetScreenHeight()
            , SDL_WINDOW_SHOWN);
        if ( m_window )
        {
            m_renderer = new Renderer( m_cmdLine, m_window );
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
    m_renderer->update();
    if ( SDL_GetTicks() > 2000 )
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{}