//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../command_line/cmd_line.h"
#include "../camera/manager.h"
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
    const commandLine::CmdLine& m_cmdLine;
    SDL_Window* m_window;
    SDL_Surface* m_surfaceLoul;
    SDL_Surface* m_surfaceCat;
    SDL_GLContext m_context;
    GLuint m_programId;
    GLint m_vertexPos;
    GLuint m_vbo;
    GLuint m_ibo;

    // This needs to be in input handling and camera management.
    SDL_Event m_event;
    bool m_userQuit = false;
    camera::Manager m_camMan;

// Functions
public:
    Renderer( const commandLine::CmdLine& arguments, SDL_Window* window );
    bool initalise();
    
    bool shutDown();
    void update();
    SDL_Texture* loadTexture( const std::string &file );
    SDL_Surface* loadBmpToSurface( const std::string &file );
    
    bool userQuit() const { return m_userQuit; }
protected:
private:
    void printProgramLog( GLuint program );
    void printShaderLog( GLuint shader );
    GLuint loadShaderFromFile( std::string path, GLenum shaderType );
    bool initGL();
    void render();
    void setMatrix( const camera::Camera& camera );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
