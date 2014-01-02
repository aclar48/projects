/**
  Author: Alex Clarke
  Dec 06 2013

  Class containing the properties for a generic object in a ray tracer
  */

#ifndef OBJECT_H
#define OBJECT_H
#include <QVector>
#include <QColor>
#include "ray.h"

class GeoObject
{
public:
    GeoObject();

    virtual ~GeoObject();

    virtual bool testIntersection(Ray &r);

    bool testFeelerInt(Ray &r);


    QVector<Ray> &intPts() const;
    void setIntPts(QVector<Ray> *intPts);

    int id() const;
    void setId(int id);

    double spec() const;
    void setSpec(double spec);

    double diff() const;
    void setDiff(double diff);

    QColor color() const;
    void setColor(const QColor &color);

    glm::vec3 trans() const;
    void setTrans(const glm::vec3 &trans);

    glm::vec3 scale() const;
    void setScale(const glm::vec3 &scale);

    double rotatex() const;
    void setRotatex(double rotatex);

    double rotatey() const;
    void setRotatey(double rotatey);

    double rotatez() const;
    void setRotatez(double rotatez);

    QString type() const;
    void setType(const QString &type);

protected:
    QVector<Ray> *_intPts;
    int _id;
    double _spec;
    double _diff;
    QColor _color;
    glm::vec3 _trans;
    glm::vec3 _scale;
    double _rotatex, _rotatey,  _rotatez;
    QString _type;


};

#endif // OBJECT_H
