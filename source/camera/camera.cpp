//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// camera/manager.cpp Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THIS include.
#include "manager.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// GLM
#include <glm/gtc/matrix_transform.hpp>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local
#include "../log/log.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace camera
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Camera::update( int frameDelta )
{
    frameDelta++;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Mat4 Camera::getMatrix() const
{
    const float _fieldOfView = 45.0f;
    const float _viewportAspectRatio = 800.0f / 400.0f;
    const float _nearPlane = 1.0f;
    const float _farPlane = 200.0f;
    const Mat4 projectionMatrix = glm::perspective( _fieldOfView
        , _viewportAspectRatio
        , _nearPlane
        , _farPlane );
    const Mat4 rot = glm::toMat4( getRot() );
    const Mat4 trans = glm::translate( Mat4( 1.0f ), Vec3( getPos() ) );
    const Mat4 final = projectionMatrix *  rot * trans;
    return final;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Camera::translate( const Vec4& translation )
{
    Mat4 rot = glm::toMat4( getRot() );
    m_position +=  translation * rot;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Camera::rotate( const Vec3& eulerRotation )
{
    m_rotation = Quat( eulerRotation ) * m_rotation;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace entity
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~