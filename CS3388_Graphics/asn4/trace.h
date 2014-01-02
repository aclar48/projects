/**
  Author: Alex Clarke
  Dec 06 2013

  Class containing the properties for a scene in a ray tracer
  */

#ifndef TRACE_H
#define TRACE_H
#include "camera.h"
#include "ray.h"
#include "sphere.h"
#include "object.h"
#include "plane.h"
#include "light.h"
#include <glm/glm.hpp>
#include "QVector"
#include "QColor"

class Trace
{
public:
    Trace();
    Trace(const Camera &cam,const int &sx,const int &sy);
    virtual ~Trace();

    Camera cam() const;
    void setCam(const Camera &cam);

    void run();

    QVector<QVector<QColor> > *pixels() const;
    void setPixels(QVector<QVector<QColor> > *pixels);


    QVector<Sphere> *slist() const;
    void setSlist(QVector<Sphere> *slist);

    Light light() const;
    void setLight(const Light &light);

    QVector<Plane> *plist() const;
    void setPlist(QVector<Plane> *plist);

    QVector<GeoObject*> *olist() const;
    void setOlist(QVector<GeoObject*> *olist);

private:
    //  QColor recursiveColor(Ray &rt, int depth);
    int _sx;
    int _sy;
    Camera _cam;
    QVector<QVector<QColor> > *_pixels;
    QVector<Sphere> *_slist;
    QVector<Plane> *_plist;
    QVector<GeoObject *> *_olist;

    Light _light;
};

#endif // TRACE_H
