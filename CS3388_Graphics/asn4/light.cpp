
/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties of a light for a ray tracer
  */

#include "light.h"

Light::Light()
{
    _pos.x = 0.0;
    _pos.y =  3.0;
    _pos.z = 0.0;
}

Light::Light(const glm::vec3 &l)
{
    _pos = l;
}
//Get and set the light position
glm::vec3 Light::pos() const
{
    return _pos;
}

void Light::setPos(const glm::vec3 &pos)
{
    _pos = pos;
}

