

/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the properties for a sphere in a ray tracer
  */
#ifndef SPHERE_H
#define SPHERE_H
#include "ray.h"
#include "camera.h"
#include "object.h"
#include <glm/glm.hpp>
#include <QVector>
#include <QColor>

class Sphere: public GeoObject
{
public:
    Sphere();
    Sphere(const int &id);
    bool testIntersection(Ray &r);
  //  bool testFeelerInt(Ray &r);

    /*
    QVector<Ray> &intPts() const;
    void setIntPts(const QVector<Ray> &intPts);
    double curT() const;
    void setCurT(double curT);

    glm::vec3 scale() const;
    void setScale(const glm::vec3 &scale);

    glm::vec3 trans() const;
    void setTrans(const glm::vec3 &trans);

    QColor color() const;
    void setColor(const QColor &color);

    double diff() const;
    void setDiff(double diff);

    double spec() const;
    void setSpec(double spec);

    int id() const;
    void setId(int id);

    double rotatex() const;
    void setRotatex(double rotatex);

    double rotatey() const;
    void setRotatey(double rotatey);

    double rotatez() const;
    void setRotatez(double rotatez);

    QString type() const;
    void setType(const QString &type);
*/
private:
/*
    QVector<Ray> *_intPts;
    int _id;
    double _curT;
    double _spec;
    double _diff;
    QColor _color;
    glm::vec3 _trans;
    glm::vec3 _scale;
    double _rotatex, _rotatey,  _rotatez;
    QString _type;
*/
    double _curT;
};

#endif // SPHERE_H
