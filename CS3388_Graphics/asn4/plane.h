#ifndef PLANE_H
#define PLANE_H
#include "ray.h"
#include "object.h"
#include <glm/glm.hpp>
#include <QVector>
#include <QColor>


class Plane: public GeoObject
{
public:
    Plane();

    Plane(const int &id);

    bool testIntersection(Ray &r);

   // bool testFeelerInt(Ray &r);

private:

};

#endif // PLANE_H
