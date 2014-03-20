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
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL_opengl.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Starts up SDL, creates window, and initializes OpenGL

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes rendering program and clear color
bool initGL();

//Input handler
void handleKeys( unsigned char key, int x, int y );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//Shader loading utility programs
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

//Graphics program
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

bool init()
{
  //Initialization flag
  bool success = true;

  //Initialize SDL
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Use OpenGL 3.1 core
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //Create window
    gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      //Create context
      gContext = SDL_GL_CreateContext( gWindow );
      if( gContext == NULL )
      {
        printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        success = false;
      }
      else
      {
        //Initialize GLEW
        glewExperimental = GL_TRUE; 
        GLenum glewError = glewInit();
        if( glewError != GLEW_OK )
        {
          printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
        }

        //Use Vsync
        if( SDL_GL_SetSwapInterval( 1 ) < 0 )
        {
          printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
        }

        //Initialize OpenGL
        if( !initGL() )
        {
          printf( "Unable to initialize OpenGL!\n" );
          success = false;
        }
      }
    }
  }

  return success;
}

bool initGL()
{
  //Success flag
  bool success = true;

  //Generate program
  gProgramID = glCreateProgram();

  //Create vertex shader
  GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

  //Get vertex source
  const GLchar* vertexShaderSource[] =
  {
    "#version 130\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
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
    glAttachShader( gProgramID, vertexShader );


    //Create fragment shader
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

    //Get fragment source
    const GLchar* fragmentShaderSource[] =
    {
      "#version 130\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
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
      glAttachShader( gProgramID, fragmentShader );


      //Link program
      glLinkProgram( gProgramID );

      //Check for errors
      GLint programSuccess = GL_TRUE;
      glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
      if( programSuccess != GL_TRUE )
      {
        printf( "Error linking program %d!\n", gProgramID );
        printProgramLog( gProgramID );
        success = false;
      }
      else
      {
        //Get vertex attribute location
        gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );
        if( gVertexPos2DLocation == -1 )
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
          glGenBuffers( 1, &gVBO );
          glBindBuffer( GL_ARRAY_BUFFER, gVBO );
          glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

          //Create IBO
          glGenBuffers( 1, &gIBO );
          glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
          glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
        }
      }
    }
  }
  
  return success;
}

void handleKeys( unsigned char key, int x, int y )
{
  //Toggle quad
  if( key == 'q' )
  {
    gRenderQuad = !gRenderQuad;
  }
}

void update()
{
  //No per frame update needed
}

void render()
{
  //Clear color buffer
  glClear( GL_COLOR_BUFFER_BIT );
  
  //Render quad
  if( gRenderQuad )
  {
    //Bind program
    glUseProgram( gProgramID );

    //Enable vertex position
    glEnableVertexAttribArray( gVertexPos2DLocation );

    //Set vertex data
    glBindBuffer( GL_ARRAY_BUFFER, gVBO );
    glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

    //Set index data and render
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

    //Disable vertex position
    glDisableVertexAttribArray( gVertexPos2DLocation );

    //Unbind program
    glUseProgram( NULL );
  }
}

void close()
{
  //Deallocate program
  glDeleteProgram( gProgramID );

  //Destroy window  
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}

void printProgramLog( GLuint program )
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

void printShaderLog( GLuint shader )
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
    init();
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
    int screenWidth = m_cmdLine.GetScreenWidth();
    int screenHeight = m_cmdLine.GetScreenHeight();
    int x = screenWidth / 2 - iW / 2;
    int y = screenHeight / 2 - iH / 2;

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