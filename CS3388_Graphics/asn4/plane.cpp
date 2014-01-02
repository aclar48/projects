
/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties for a plane in a ray tracer
  */
#include "plane.h"
#include <iostream>
#define HIT_TOLERANCE 0.25
#define SIZE 0.1
Plane::Plane()
{
}

Plane::Plane(const int &id)
{
    _id = id;
    _type = "plane";
}
//Test to see if a ray intersects the generic sphere
bool Plane::testIntersection(Ray &r)
{
    if(glm::abs(r.c().z) > 0.01) {
        double t = -glm::normalize(r.e()).z/glm::normalize(r.c()).z;
        //std::cout << t << std::endl;
        r.setT(t);
        //std::cout << r.getIntPoint().x << std::endl;
        if (r.getIntPoint().x > SIZE || r.getIntPoint().y > SIZE || r.getIntPoint().x < -SIZE || r.getIntPoint().y < -SIZE) return false;

        r.setN(glm::vec3(0,0,-1));
        _intPts->append(r);
        return true;
    } return false;

}
/*
//Test to see if a feeler ray hits this object
bool Plane::testFeelerInt(Ray &r)
{
    for(QVector<Ray>::iterator it = _intPts->begin(); it != _intPts->end(); ++it) {
        glm::vec3 comp = it->getIntPoint()-r.e();
        double tx = comp.x/r.c().x;
        double ty = comp.y/r.c().y;
        double tz = comp.z/r.c().z;
        if(tx > 1.0 || ty > 1.0 || tz > 1.0) return false;
        else {
            if(glm::abs(tx-ty) < HIT_TOLERANCE && glm::abs(tx-tz) < HIT_TOLERANCE && glm::abs(tx-ty) < HIT_TOLERANCE && glm::abs(ty-tz) < HIT_TOLERANCE) {
                std::cout << "hit" << std::endl;
               return true;
            }
            else return false;
        }
    }
    return false;
}
*/
