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
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;
struct SDL_Color;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
    class Hopper;
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
    render::Manager& m_renderMan;
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
    Renderer( Hopper& hopper, SDL_Window* window );
    bool initalise();
    
    bool shutDown();
    void update();
    SDL_Texture* loadTexture( const String &file );
    SDL_Surface* loadBmpToSurface( const String &file );
    
    bool userQuit() const { return m_userQuit; }
protected:
private:
    void printProgramLog( GLuint program );
    void printShaderLog( GLuint shader );
    GLuint loadShaderFromFile( String path, GLenum shaderType );
    bool initGL();
    void render();
    void setMatrix( const camera::Camera& camera );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
