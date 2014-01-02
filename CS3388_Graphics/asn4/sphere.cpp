

/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties for a sphere in a ray tracer
  */
#include "sphere.h"
#include <iostream>
#define HIT_TOLERANCE 0.25

Sphere::Sphere()
{
    _diff = 0.7;
    _spec = 1.0;
    _color = QColor(255,0,255);

}
//Construct a sphere of given id
Sphere::Sphere(const int &id)
{
 _id = id;


}


//Generate a generice sphere
bool Sphere::testIntersection(Ray &r)
{
    double b = glm::dot(r.e(),r.c());
    double c = glm::dot(r.e(),r.e()) -1.0;

    double qf = b*b-c;
    if (qf > 0.0) {
        double t1 = -b + glm::sqrt(qf);
        double t2 = -b - glm::sqrt(qf);
        _curT = glm::min(t1,t2);
        r.setT(_curT);
        r.setN(glm::normalize(r.getIntPoint()));
        _intPts->append(r);
        return true;
    }
    return false;

}
/*
//Test to see if a feeler ray hits this object
bool Sphere::testFeelerInt(Ray &r)
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
/*
//Get and set the list of intersecting rays
QVector<Ray> &Sphere::intPts() const
{
    return *_intPts;
}

void Sphere::setIntPts(const QVector<Ray> &intPts)
{
    *_intPts = intPts;
}
//Get and set current T value
double Sphere::curT() const
{
    return _curT;
}

void Sphere::setCurT(double curT)
{
    _curT = curT;
}

//Get and set Scale
glm::vec3 Sphere::scale() const
{
    return _scale;
}

void Sphere::setScale(const glm::vec3 &scale)
{
    _scale = scale;
}
//Get and set Translation
glm::vec3 Sphere::trans() const
{
    return _trans;
}

void Sphere::setTrans(const glm::vec3 &trans)
{
    _trans = trans;
}
//Get and set color
QColor Sphere::color() const
{
    return _color;
}

void Sphere::setColor(const QColor &color)
{
    _color = color;
}
//Get and set Diffuse reflection
double Sphere::diff() const
{
    return _diff;
}

void Sphere::setDiff(double diff)
{
    _diff = diff;
}
//Get and set specular reflection
double Sphere::spec() const
{
    return _spec;
}

void Sphere::setSpec(double spec)
{
    _spec = spec;
}
//Get and set object id
int Sphere::id() const
{
    return _id;
}

void Sphere::setId(int id)
{
    _id = id;
}
//Get and set x rotation
double Sphere::rotatex() const
{
    return _rotatex;
}

void Sphere::setRotatex(double rotatex)
{
    _rotatex = rotatex;
}
//Get and set y rotation
double Sphere::rotatey() const
{
    return _rotatey;
}

void Sphere::setRotatey(double rotatey)
{
    _rotatey = rotatey;
}
//Get and set z rotation
double Sphere::rotatez() const
{
    return _rotatez;
}

void Sphere::setRotatez(double rotatez)
{
    _rotatez = rotatez;
}


QString Sphere::type() const
{
    return _type;
}

void Sphere::setType(const QString &type)
{
    _type = type;
}

*/
