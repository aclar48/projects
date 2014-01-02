
/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties for a ray in a ray tracer
  */
#include "ray.h"

Ray::Ray()
{

}
//Create a ray of given parameters
Ray::Ray(const vec3 &e, const vec3 &c, const double &t)
{
//    _e = glm::normalize(e);
    _e = e;
    _c = c;
    _t = t;
}
//Get and set the eye
vec3 Ray::e() const
{
    return _e;
}

void Ray::setE(const vec3 &e)
{
    _e = e;
}
//Get and set the direction
vec3 Ray::c() const
{
    return _c;
}

void Ray::setC(const vec3 &c)
{
    _c = c;
}
//Get and set t
double Ray::t() const
{
    return _t;
}

void Ray::setT(double t)
{
    _t = t;
}
//Convert from ray to point in normalized x,y
vec3 Ray::getIntPoint() const
{
    vec3 c(_c.x*_t,_c.y*_t,_c.z*_t);
    return _e + c;
}
//Get and set the normal
vec3 Ray::n() const
{
    return _n;
}

void Ray::setN(const vec3 &n)
{
    _n = n;
}




