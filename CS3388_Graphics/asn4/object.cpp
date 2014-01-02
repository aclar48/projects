/**
  Author: Alex Clarke
  Dec 06 2013

  Class containing the properties for a generic object in a ray tracer
  */
#include "object.h"
#include <iostream>
#define HITT 0.5

GeoObject::GeoObject():_intPts(new QVector<Ray>())
{
}

GeoObject::~GeoObject()
{
}

bool GeoObject::testIntersection(Ray &r)
{
    return false;
}
//Test if a feeler ray intersects
bool GeoObject::testFeelerInt(Ray &r)
{
    for(QVector<Ray>::iterator it = _intPts->begin(); it != _intPts->end(); ++it) {
        glm::vec3 point = it->getIntPoint();
        double xt = (point.x - r.e().x)/(r.c().x - r.e().x);
        double yt = (point.y - r.e().y)/(r.c().y - r.e().y);
        double zt = (point.z - r.e().z)/(r.c().z - r.e().z);
        if(glm::abs(xt - yt) < HITT && glm::abs(xt -zt) < HITT && glm::abs(yt - zt) < HITT) {
            if(xt > 1.0) {
                std::cout << "hit" << std::endl;
                return true;

            }
        }
    }
    return false;
}
//Set and get the z axis rotation
double GeoObject::rotatez() const
{
    return _rotatez;
}

void GeoObject::setRotatez(double rotatez)
{
    _rotatez = rotatez;
}
//Set and get the y axis rotation
double GeoObject::rotatey() const
{
    return _rotatey;
}

void GeoObject::setRotatey(double rotatey)
{
    _rotatey = rotatey;
}
//Set and get the x axis rotation
double GeoObject::rotatex() const
{
    return _rotatex;
}

void GeoObject::setRotatex(double rotatex)
{
    _rotatex = rotatex;
}
//Set and get the scaling
glm::vec3 GeoObject::scale() const
{
    return _scale;
}

void GeoObject::setScale(const glm::vec3 &scale)
{
    _scale = scale;
}
//Set and get the translation
glm::vec3 GeoObject::trans() const
{
    return _trans;
}

void GeoObject::setTrans(const glm::vec3 &trans)
{
    _trans = trans;
}
//Set and get the colour
QColor GeoObject::color() const
{
    return _color;
}

void GeoObject::setColor(const QColor &color)
{
    _color = color;
}
//Set and get the diffuse reflection
double GeoObject::diff() const
{
    return _diff;
}

void GeoObject::setDiff(double diff)
{
    _diff = diff;
}
//Set and get the specular reflection
double GeoObject::spec() const
{
    return _spec;
}

void GeoObject::setSpec(double spec)
{
    _spec = spec;
}
// Set and get the id
int GeoObject::id() const
{
    return _id;
}

void GeoObject::setId(int id)
{
    _id = id;
}
//Set and get the list of intersection points
QVector<Ray> &GeoObject::intPts() const
{
    return *_intPts;
}

void GeoObject::setIntPts(QVector<Ray> *intPts)
{
    _intPts = intPts;
}



//Set and get the id for the type
QString GeoObject::type() const
{
    return _type;
}

void GeoObject::setType(const QString &type)
{
    _type = type;
}
