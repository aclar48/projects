

/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties of a light for a ray tracer
  */

#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>

class Light
{
public:
    Light();
    Light(const glm::vec3 &l);


    glm::vec3 pos() const;
    void setPos(const glm::vec3 &pos);

private:

    glm::vec3 _pos;
};

#endif // LIGHT_H
