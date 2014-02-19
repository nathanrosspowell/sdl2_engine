//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// sdl2_engine.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <iostream>
#include <cstdint> 
#include <vector> 
#include <string>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
#include "SDL_image.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local
#include "command_line/base.h"
#include "game/application.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError( std::ostream &os, const std::string& msg )
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads an image into a texture on the rendering device
* @param file The image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr)		
		logSDLError(std::cout, "LoadTexture");
	return texture;
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param renderer The renderer we want to draw too
* @param x The x coordinate to draw too
* @param y The y coordinate to draw too
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *renderer, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(renderer, tex, NULL, &dst);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main( int argc, const char* const argv[])
{
    // Create the arguments class
    std::vector< std::string > arguments;
    for ( int i = 0; i < argc; ++i )
    {
        arguments.push_back( argv[ i ] );
    }
    commandLine::Base cmdLine( arguments );
    // Create the application.
    game::Application application( cmdLine );
    application.update();

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
	    std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	    return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Hello World!", 10, 10, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
	    std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    	return 1;
    }
  
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
	    std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    	return 1;
    }  
   
    SDL_Texture *background  = loadTexture("../resources/image/test.bmp", renderer);
    SDL_Texture *image  = loadTexture("../resources/image/cat.bmp", renderer);
    
    SDL_RenderClear(renderer);
     
    int bW, bH;
    SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
    renderTexture(background, renderer, 0, 0);
    renderTexture(background, renderer, bW, 0);
    renderTexture(background, renderer, 0, bH);
    renderTexture(background, renderer, bW, bH);
     
    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;
    renderTexture(image, renderer, x, y);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
