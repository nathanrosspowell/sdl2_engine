//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../command_line/base.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL_opengl.h>


class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Texture;
class SDL_Rect;
class SDL_Color;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{

class Renderer
{
public:
protected:
private:
// Variables
public:
protected:
private:
    const commandLine::Base& m_cmdLine;
    SDL_Window* m_window;
    SDL_Texture* m_background;
    SDL_Texture* m_image;
    SDL_GLContext m_context;
    GLuint m_programIDbo = 0;
    GLint m_vertexPos2DLocation = -1;
    GLuint m_vbo = 0;
    GLuint m_ibo = 0;

// Functions
public:
    
    bool init();

    //Initializes rendering program and clear color
    bool initGL();

    //Input handler
    void handleKeys( unsigned char key, int x, int y );
    //Renders quad to the screen
    void render();

    //Frees media and shuts down SDL
    void close();
//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );


    Renderer( const commandLine::Base& arguments, SDL_Window* window );
    bool initalise();
    bool shutDown();
    void update();
    bool draw( SDL_Texture* texture
             , int x
             , int y
             , double rotation );
    bool draw( SDL_Texture* texture
             , int x
             , int y
             , int x2
             , int y2
             , int w
             , int h
             , double rotation );
    bool draw( SDL_Texture* texture
             , int x
             , int y
             , SDL_Rect& rect
             , double rotation );
    bool draw( int x
             , int y
             , int w
             , int h
             , SDL_Color& color
             , double rotation );
    SDL_Texture* loadTexture( const std::string &file );
protected:
private:
};

}