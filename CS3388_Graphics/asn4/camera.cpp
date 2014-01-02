/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties of a camera for a ray tracer
  */

#include "camera.h"
#include <QDebug>
#define VANGLE 0.7853981633974483096 //45 deg in radians
Camera::Camera()
{
}
// Construct a camera of given parametes
Camera::Camera(const glm::vec3 &e, const glm::vec3 &g, const glm::vec3 &p,const double &near,const double &aspect)
{
    _e = e;
    _n = glm::normalize(e-g);
    qDebug() << _n.x << "," << _n.y << "," << _n.z;
    _u = glm::normalize(glm::cross(p,_n));
    _v = glm::normalize(glm::cross(_u,_n));
    _near = near;


   _wHeight = _near * glm::tan(VANGLE/2);
   _wWidth = _wHeight*aspect;
    qDebug() << aspect;
    qDebug() << "wHeight:" << _wHeight << " wWidth:" << _wWidth;
}
//Get and set u
glm::vec3 Camera::u() const
{
    return _u;
}

void Camera::setU(const glm::vec3 &u)
{
    _u = u;
}
// Get and set v
glm::vec3 Camera::v() const
{
    return _v;
}

void Camera::setV(const glm::vec3 &v)
{
    _v = v;
}
// Get and set n
glm::vec3 Camera::n() const
{
    return _n;
}

void Camera::setN(const glm::vec3 &n)
{
    _n = n;
}
// Get and set e
glm::vec3 Camera::e() const
{
    return _e;
}

void Camera::setE(const glm::vec3 &e)
{
    _e = e;
}
// Get and set distance to near plane
double Camera::near() const
{
    return _near;
}

void Camera::setNear(double near)
{
    _near = near;
}
// Get and set near plane Height
double Camera::wHeight() const
{
    return _wHeight;
}

void Camera::setWHeight(double wHeight)
{
    _wHeight = wHeight;
}
// Get and set near plane width
double Camera::wWidth() const
{
    return _wWidth;
}

void Camera::setWWidth(double wWidth)
{
    _wWidth = wWidth;
}







