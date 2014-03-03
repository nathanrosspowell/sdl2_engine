//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "renderer.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
#include "SDL_image.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Renderer::Renderer( const commandLine::Base& cmdLine, SDL_Window* window )
: m_cmdLine( cmdLine )
, m_window( window )
, m_background( nullptr )
, m_image( nullptr )
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::initalise()
{
    stateStd( "" );
    m_renderer = SDL_CreateRenderer( m_window
        , -1
        , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( m_renderer == nullptr )
    {
        errorStd( "SDL_CreateRenderer Error: " << SDL_GetError() );
    }
    m_background = loadTexture( "../resources/image/test.bmp" );
    m_image = loadTexture( "../resources/image/cat.bmp" );
}
bool Renderer::shutDown()
{
    stateStd( "" );
    SDL_DestroyTexture( m_background );
    SDL_DestroyTexture( m_image );
    SDL_DestroyRenderer( m_renderer );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Renderer::update()
{
    SDL_RenderPresent( m_renderer );
    SDL_RenderClear( m_renderer );

    int iW, iH;
    SDL_QueryTexture( m_image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;

    x += SDL_GetTicks() % 100;
    y += SDL_GetTicks() % 100;

    int bW, bH;
    SDL_QueryTexture( m_background, NULL, NULL, &bW, &bH);
    draw( m_background, 0, 0, 0.0 );
    draw( m_background, bW, 0, 0.0 );
    draw( m_background, 0, bH, 0.0 );
    draw( m_background, bW, bH, 0.0 );

    SDL_QueryTexture(m_image, NULL, NULL, &iW, &iH);
    draw( m_image, x, y, 0.0 );

    SDL_RenderPresent( m_renderer );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::draw( SDL_Texture* texture
                   , int x
                   , int y
                   , double rotation )
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture( texture, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy( m_renderer, texture, NULL, &dst);
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::draw( SDL_Texture* texture
                   , int x
                   , int y
                   , int x2
                   , int y2
                   , int w
                   , int h
                   , double rotation )
{
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::draw( SDL_Texture* texture
                   , int x
                   , int y
                   , SDL_Rect& rect
                   , double rotation )
{
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::draw( int x
                   , int y
                   , int w
                   , int h
                   , SDL_Color& color
                   , double rotation )
{
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SDL_Texture* Renderer::loadTexture( const std::string &file )
{
    SDL_Texture* texture = IMG_LoadTexture( m_renderer, file.c_str());
    if ( texture == nullptr )
    {
        errorStd( "Missing texture: " << file << " SDL:" << SDL_GetError() );
    }
    return texture;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~