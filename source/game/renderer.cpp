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
//Starts up SDL, creates window, and initializes OpenGL
//Graphics program
bool Renderer::init()
{
    //Initialization flag
    bool success = true;
    //Create context
    m_context = SDL_GL_CreateContext( m_window );
    if( m_context == NULL )
    {
        errorStd( "OpenGL context could not be created! SDL Error:" << SDL_GetError() );
        success = false;
    }
    else
    {
        //Initialize GLEW
        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if( glewError != GLEW_OK )
        {
            errorStd( "Error initializing GLEW! Error:" << glewGetErrorString( glewError ) );
        }
        //Use Vsync
        if( SDL_GL_SetSwapInterval( 1 ) < 0 )
        {
            errorStd( "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() );
        }
        //Initialize OpenGL
        if( !initGL() )
        {
            errorStd( "Unable to initialize OpenGL!" );
            success = false;
        }
    }
    return success;
}

bool Renderer::initGL()
{
    //Success flag
    bool success = true;
    //Generate program
    m_programIDbo = glCreateProgram();
    //Create vertex shader
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    //Get vertex source
    const GLchar* vertexShaderSource[] =
    {
        "#version 120\n"
        "attribute vec2 LVertexPos2D;"
        "void main()"
        "{"
            "gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 );"
        "}"
    };
    //Set vertex source
    glShaderSource( vertexShader, 1, vertexShaderSource, NULL );
    //Compile vertex source
    glCompileShader( vertexShader );
    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
    if( vShaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile vertex shader %d!\n", vertexShader );
        printShaderLog( vertexShader );
        success = false;
    }
    else
    {
        //Attach vertex shader to program
        glAttachShader( m_programIDbo, vertexShader );
        //Create fragment shader
        GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
        //Get fragment source
        const GLchar* fragmentShaderSource[] =
        {
            "#version 120\n"
            "void main()"
            "{"
                "gl_FragColor = vec4( 0.0, 1.0, 0.6, 1.0 );"
            "}"
        };
        //Set fragment source
        glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );
        //Compile fragment source
        glCompileShader( fragmentShader );
        //Check fragment shader for errors
        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
        if( fShaderCompiled != GL_TRUE )
        {
            printf( "Unable to compile fragment shader %d!\n", fragmentShader );
            printShaderLog( fragmentShader );
            success = false;
        }
      else
      {
            //Attach fragment shader to program
            glAttachShader( m_programIDbo, fragmentShader );
            //Link program
            glLinkProgram( m_programIDbo );
            //Check for errors
            GLint programSuccess = GL_TRUE;
            glGetProgramiv( m_programIDbo, GL_LINK_STATUS, &programSuccess );
            if( programSuccess != GL_TRUE )
            {
                printf( "Error linking program %d!\n", m_programIDbo );
                printProgramLog( m_programIDbo );
                success = false;
            }
            else
            {
                //Get vertex attribute location
                m_vertexPos2DLocation = glGetAttribLocation( m_programIDbo, "LVertexPos2D" );
                if( m_vertexPos2DLocation == -1 )
                {
                    printf( "LVertexPos2D is not a valid glsl program variable!\n" );
                    success = false;
                }
                else
                {
                    //Initialize clear color
                    glClearColor( 0.f, 0.f, 0.f, 1.f );
                    //VBO data
                    GLfloat vertexData[] =
                    {
                        -0.5f, -0.5f,
                        0.5f, -0.5f,
                        0.5f,  0.5f,
                        -0.5f,  0.5f
                    };
                    //IBO data
                    GLuint indexData[] = { 0, 1, 2, 3 };
                    //Create VBO
                    glGenBuffers( 1, &m_vbo );
                    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
                    glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );
                    //Create IBO
                    glGenBuffers( 1, &m_ibo );
                    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
                    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
                }
            }
        }
    }
    return success;
}

void  Renderer::render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    //Bind program
    glUseProgram( m_programIDbo );
    //Enable vertex position
    glEnableVertexAttribArray( m_vertexPos2DLocation );
    //Set vertex data
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glVertexAttribPointer( m_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );
    //Set index data and render
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ibo );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );
    //Disable vertex position
    glDisableVertexAttribArray( m_vertexPos2DLocation );
    //Unbind program
    glUseProgram( 0 );
}

void  Renderer::close()
{
    //Deallocate program
    glDeleteProgram( m_programIDbo );
    //Destroy window  
    SDL_DestroyWindow( m_window );
    m_window = NULL;
    //Quit SDL subsystems
    SDL_Quit();
}

void  Renderer::printProgramLog( GLuint program )
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
            printf( "%s\n", infoLog );
        }
        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a program\n", program );
    }
}

void  Renderer::printShaderLog( GLuint shader )
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
            printf( "%s\n", infoLog );
        }
        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Renderer::Renderer( const commandLine::Base& cmdLine, SDL_Window* window )
: m_cmdLine( cmdLine )
, m_window( window )
, m_background( nullptr )
, m_image( nullptr )
, m_programIDbo( 0 )
, m_vertexPos2DLocation( -1 )
, m_vbo( 0 )
, m_ibo( 0 )
{

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Renderer::initalise()
{
    stateStd( "" );
    m_background = loadTexture( "../resources/image/test.bmp" );
    m_image = loadTexture( "../resources/image/cat.bmp" );
    init();
}
bool Renderer::shutDown()
{
    stateStd( "" );
    SDL_DestroyTexture( m_background );
    SDL_DestroyTexture( m_image );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Renderer::update()
{
    //Render quad
    render();
    
    //Update screen
    SDL_GL_SwapWindow( m_window );
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
    //SDL_QueryTexture( texture, NULL, NULL, &dst.w, &dst.h);
    //SDL_RenderCopy( m_renderer, texture, NULL, &dst);
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
    SDL_Texture* texture = nullptr;// = IMG_LoadTexture( m_renderer, file.c_str());
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