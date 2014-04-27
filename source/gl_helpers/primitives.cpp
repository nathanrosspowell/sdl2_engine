//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// gl_helpers/primivites.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This header.
#include "primitives.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// SDL and GL
#include <GL/glew.h>
#include <GL/glu.h>
#include <SDL_opengl.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace gl_helpers
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace primitives
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cube( float size, const Vec3& vec3 )
{
    cube( size, vec3.x, vec3.y, vec3.z );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cube( float size, float x, float y, float z )
{
    cuboid( size, size, size, x, y, z );
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void cuboid( float h, float w, float d, float x, float y, float z )
{
    const float hh = h / 2; // Half height.
    const float hw = w / 2; // Half width.
    const float hd = d / 2; // Half depth.
    const float xp = x + hw; // X positive
    const float xn = x - hw; // X negative
    const float yp = y + hh; // Y positive
    const float yn = y - hh; // Y negative
    const float zp = z + hd; // Z positive
    const float zn = z - hd; // Z negative
    // White side - BACK
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  1.0, 1.0 );
        glVertex3f( xp, yn, zp );
        glVertex3f( xp, yp, zp );
        glVertex3f( xn, yp, zp );
        glVertex3f( xn, yn, zp );
    glEnd();
    // Purple side - RIGHT
    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  1.0 );
        glVertex3f( xp, yn, zn );
        glVertex3f( xp, yp, zn );
        glVertex3f( xp, yp, zp );
        glVertex3f( xp, yn, zp );
    glEnd();
    // Green side - LEFT
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0,  0.0 );
        glVertex3f( xn, yn, zp );
        glVertex3f( xn, yp, zp );
        glVertex3f( xn, yp, zn );
        glVertex3f( xn, yn, zn );
    glEnd();
    // Blue side - TOP
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  0.0,  1.0 );
        glVertex3f( xp, yp, zp );
        glVertex3f( xp, yp, zn );
        glVertex3f( xn, yp, zn );
        glVertex3f( xn, yp, zp );
    glEnd();
    // Red side - BOTTOM
    glBegin(GL_POLYGON);
    glColor3f(   1.0,  0.0,  0.0 );
        glVertex3f( xp, yn, zn );
        glVertex3f( xp, yn, zp );
        glVertex3f( xn, yn, zp );
        glVertex3f( xn, yn, zn );
    glEnd();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~