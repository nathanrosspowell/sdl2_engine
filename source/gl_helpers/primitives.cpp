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
void cube( float size, float x, float y, float z )
{
    const float hs = size / 2; // Half size.
    const float xp = x + hs; // X positive
    const float xn = x - hs; // X negative
    const float yp = y + hs; // Y positive
    const float yn = y - hs; // Y negative
    const float zp = z + hs; // Z positive
    const float zn = z - hs; // Z negative
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