//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../command_line/base.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL and GL.
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL_opengl.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Forward decleration.
class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Surface;
class SDL_Rect;
class SDL_Color;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
    SDL_Surface* m_surfaceLoul;
    SDL_Surface* m_surfaceCat;
    SDL_GLContext m_context;
    GLuint m_programId;
    GLint m_vertexPos;
    GLuint m_vbo;
    GLuint m_ibo;


// Functions
public:
    Renderer( const commandLine::Base& arguments, SDL_Window* window );
    bool initalise();
    bool initGL();
    bool shutDown();
    void update();
    void render();
    SDL_Texture* loadTexture( const std::string &file );
    SDL_Surface* loadBmpToSurface( const std::string &file );
    void printProgramLog( GLuint program );
    void printShaderLog( GLuint shader );
    GLuint loadShaderFromFile( std::string path, GLenum shaderType );
protected:
private:
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
