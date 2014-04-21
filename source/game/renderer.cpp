//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "renderer.h"
#include "hopper.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL.
#include "SDL.h"
#include "SDL_image.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// STD library.
#include <fstream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// gl_helpers.
#include "../gl_helpers/primitives.h"
#include "../command_line/auto_close_timer.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLM.
#include "../types/glm.hxx"
#include <glm/gtc/type_ptr.hpp>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Renderer::Renderer( Hopper& hopper, SDL_Window* window )
: m_cmdLine( hopper.getCmdLine() )
, m_renderMan( hopper.getRenderMan() )
, m_window( window )
, m_surfaceLoul( nullptr )
, m_surfaceCat( nullptr )
, m_programId( 0 )
, m_vertexPos( -1 )
, m_vbo( 0 )
, m_ibo( 0 )
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::initalise()
{
    stateStd( "" );
    m_surfaceLoul = loadBmpToSurface( "../resources/image/test.bmp" );
    stateStd( "" );
    
    m_surfaceCat = loadBmpToSurface( "../resources/image/cat.bmp" );
        //Initialization flag
    bool success = true;
    //Create context
    stateStd( "" );
    
    m_context = SDL_GL_CreateContext( m_window );
    stateStd( "" );
    
    if( m_context == NULL )
    {
        errorStd( "OpenGL not created! SDL Error:" << SDL_GetError() );
        success = false;
    }
    else
    {
    stateStd( "" );

        //Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum error = glewInit();
        if( error != GLEW_OK )
        {
            errorStd( "Initializing GLEW: " << glewGetErrorString( error ) );
        }
        //Use Vsync
        if( SDL_GL_SetSwapInterval( 1 ) < 0 )
        {
            errorStd( "Unable to set VSync! SDL Error: " << SDL_GetError() );
        }
        //Initialize OpenGL
        if( !initGL() )
        {
            errorStd( "Unable to initialize OpenGL!" );
            success = false;
        }
    }
    stateStd( "DONJE" );

    return success;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::initGL()
{
    //Generate program
    m_programId = glCreateProgram();
    //Create vertex shader
    String vertexPath = "../source/shaders/vertex/vert_0.glvs";
    GLuint vertexId = loadShaderFromFile( vertexPath, GL_VERTEX_SHADER );
    if( vertexId == 0 )
    {
        return false;
    }
    else
    {
        //Attach vertex shader to program
        glAttachShader( m_programId, vertexId );
    }
    //Create vertex shader
    String fragmentPath = "../source/shaders/fragment/frag_0.glfs";
    GLuint fragmentId = loadShaderFromFile( fragmentPath, GL_FRAGMENT_SHADER );
    if( fragmentId == 0 )
    {
        errorStd( "Can't compile fragment shader: " << fragmentId );
        return false;
    }
    //Attach fragment shader to program
    glAttachShader( m_programId, fragmentId );
    //Link program
    glLinkProgram( m_programId );
    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv( m_programId, GL_LINK_STATUS, &programSuccess );
    if( programSuccess != GL_TRUE )
    {
        errorStd( "Error linking program: " << m_programId );
        printProgramLog( m_programId );
        return false;
    }
    //Get vertex attribute location
    m_vertexPos = glGetAttribLocation( m_programId, "LVertexPos2D" );
    if( m_vertexPos == -1 )
    {
        errorStd( "LVertexPos2D is not a valid glsl program variable." );
        return false;
    }
    //Initialize clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);//VBO data
    GLfloat vertexData[] =
    {
        -1.5f, -1.5f,
        -0.5f, -1.5f,
        -0.5f,  -0.5f,
        -1.5f,  -0.2f
    };
    //IBO data
    GLuint indexData[] = { 0, 1, 2, 3 };
    //Create VBO
    glGenBuffers( 1, &m_vbo );
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER
      , 2 * 4 * sizeof(GLfloat)
      , vertexData
      , GL_STATIC_DRAW );
    //Create IBO
    glGenBuffers( 1, &m_ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER
      , 4 * sizeof(GLuint)
      , indexData
      , GL_STATIC_DRAW );
        return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::shutDown()
{
    stateStd( "" );
    SDL_FreeSurface( m_surfaceLoul );
    SDL_FreeSurface( m_surfaceCat );
    glDeleteProgram( m_programId );
    return true;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Renderer::update()
{
    Vec4 pos( 0.0f );
    Vec3 rot( 0.0f );
    /****** Check for Key & System input ******/    
    while ( SDL_PollEvent( &m_event ) )
    {
        const float speed = 0.01f;
        switch ( m_event.type )
        {
        case SDL_KEYDOWN:
            {
                auto keyPressed = m_event.key.keysym.sym;
                switch ( keyPressed )
                {
                case SDLK_w: pos.z += speed; break;
                case SDLK_s: pos.z -= speed; break;
                case SDLK_y: pos.y += speed; break;
                case SDLK_h: pos.y -= speed; break;
                case SDLK_a: pos.x += speed; break;
                case SDLK_d: pos.x -= speed; break;
                case SDLK_i: rot.x += speed; break;
                case SDLK_k: rot.x -= speed; break;
                case SDLK_j: rot.y += speed; break;
                case SDLK_l: rot.y -= speed; break;
                }
            }
            break;
        case SDL_QUIT:
            stateStd( "User Quit" );
            m_userQuit = true;
            break;
        }
    }
    auto& cam = m_camMan.getCameraForEdit();
    cam.rotate( rot );
    cam.translate( pos );
    //Render quad
    render();
    //Update screen
    SDL_GL_SwapWindow( m_window );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void  Renderer::render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
    // Reset transformations
    glLoadIdentity();

    setMatrix( m_camMan.getCamera() );
    // Draw cubes.
    //gl_helpers::primitives::cube( 1.0, 0.0f, 0.0f, 0.0f );
    //gl_helpers::primitives::cuboid( 0.5f, 0.1f, 0.1f,  -1.1f, 0.0f, 0.0f );
    //gl_helpers::primitives::cuboid( 0.1f, 0.5f, 0.1f,  1.1f, 0.0f, 0.0f );
    m_renderMan.update();
    // Set Camera.
    glLoadIdentity();
    //Bind program
    glUseProgram( m_programId );
    //Enable vertex position
    glEnableVertexAttribArray( m_vertexPos );
    //Set vertex data
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glVertexAttribPointer( m_vertexPos
      , 2
      , GL_FLOAT
      , GL_FALSE
      , 2 * sizeof(GLfloat)
      , NULL );
    //Set index data and render
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
    //Disable vertex position
    glDisableVertexAttribArray( m_vertexPos );
    //Unbind program
    glUseProgram( 0 );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SDL_Surface* Renderer::loadBmpToSurface( const String& file )
{
    stateStd( "" );

    SDL_Surface* surface = SDL_LoadBMP( file.c_str() );
    if ( surface == nullptr )
    {
        errorStd( "Missing surface: " << file << " SDL:" << SDL_GetError() );
    }
    stateStd( "" );
    
    return surface;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Renderer::printProgramLog( GLuint program )
{
    //Make sure name is shader
    if( glIsProgram( program ) )
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
        //Allocate string
        char* infoLog = new char[ maxLength ];
        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            errorStd( infoLog );
        }
        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        errorStd( "Name " << program << " is not a program" );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Renderer::printShaderLog( GLuint shader )
{
    //Make sure name is shader
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
        //Allocate string
        char* infoLog = new char[ maxLength ];
        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            errorStd( infoLog );
        }
        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        errorStd( "Name " << shader << " is not a shader" );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
GLuint Renderer::loadShaderFromFile( String path, GLenum shaderType )
{
    GLuint shaderId = 0;
    std::ifstream sourceFile( path.c_str() );
    if ( sourceFile )
    {
        auto stream = std::istreambuf_iterator< char >( sourceFile );
        auto iterator = std::istreambuf_iterator< char >();
        String shaderString;
        shaderString.assign( stream, iterator );
        shaderId = glCreateShader( shaderType );
        const GLchar* shaderSource = shaderString.c_str();
        glShaderSource( shaderId, 1, (const GLchar**)&shaderSource, NULL );
        glCompileShader( shaderId );
        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv( shaderId, GL_COMPILE_STATUS, &shaderCompiled );
        if ( shaderCompiled != GL_TRUE )
        {
            errorStd( "Can't compile shader. Id:" 
                << shaderId 
                << "Source:" 
                << shaderSource );
            printShaderLog( shaderId );
            glDeleteShader( shaderId );
            shaderId = 0;
        }
    }
    else
    {
        errorStd( "Unable to open file:" << path.c_str() );
    }
    return shaderId;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Renderer::setMatrix( const camera::Camera& camera )
{
    Mat4 matrix = camera.getMatrix();
    glLoadMatrixf( glm::value_ptr( matrix ) );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace game.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~