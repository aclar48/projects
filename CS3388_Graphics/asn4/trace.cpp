
/**
  Author: Alex Clarke
  Dec 06 2013

  Class containing the properties for a scene in a ray tracer
  */
#include "trace.h"
#include "matrixoperations.h"
#include <iostream>
#include <float.h>
#define AMBIENT 0.4;
#define MAXDEPTH 4;

Trace::Trace():_pixels(new QVector<QVector<QColor> >())
{
}
//Create a scene of given parameters
Trace::Trace(const Camera &cam, const int &sx, const int &sy):_pixels(new QVector<QVector<QColor> >()), _slist(new QVector<Sphere>()), _plist(new QVector<Plane>()), _olist(new QVector<GeoObject*>())
{
    _cam = cam;
    _sx = sx;
    _sy = sy;
    for(int i = 0; i < _sx; ++i) {
        _pixels->append(QVector<QColor>());
        for(int j = 0; j < _sy; ++j) {
            _pixels->operator [](i).append(QColor(255,255,255));
        }
    }
    std::cout << "done" << std::endl;
}
//Destructor
Trace::~Trace()
{
    delete _pixels;
    delete _slist;

}
//Get and set the camera
Camera Trace::cam() const
{
    return _cam;
}

void Trace::setCam(const Camera &cam)
{
    _cam = cam;
}
// Do some ray tracing
void Trace::run()
{
    for(double i = _sx/2; i < _sx +_sx/2; i += 1.0) {
        for(double j = _sy/2; j < _sy + _sy/2; j += 1.0) {
           float uc = -_cam.wWidth() + _cam.wWidth()*(2*i/_sx - 1.0);
           float uv = -_cam.wHeight() + _cam.wHeight()*(2*j/_sy -1.0);
           QColor pixCol(255,255,255);
           glm::vec3 dir = -(float)_cam.near()*_cam.n() + uc*_cam.u() + uv*_cam.v();
           dir = glm::normalize(dir);
           Ray rt(_cam.e(),dir,0.0);
           bool didint = false;
           for(QVector<GeoObject*>::iterator stt = _olist->begin(); stt != _olist->end(); ++stt) {
               GeoObject *st = *stt;
               Ray rtt(_cam.e(),dir,0.0);

               rtt = MatrixOperations::scaleTransform(st->scale(),rtt);
               rtt = MatrixOperations::transTransform(st->trans(),rtt);
               rtt = MatrixOperations::rotateXTransform(st->rotatex(),rtt);
               rtt = MatrixOperations::rotateYTransform(st->rotatey(),rtt);
               rtt = MatrixOperations::rotateZTransform(st->rotatez(),rtt);
               if(st->type() == "sphere")  {
                   Sphere *sst = dynamic_cast<Sphere*>(st);

                   if(sst->testIntersection(rtt)) {

                       didint = true;
                       rt = rtt;
                   }
               }
               else if(st->type() == "plane") {
                   Plane *sst = (Plane*)st;
                   if(sst->testIntersection(rtt)) {

                       didint = true;
                       rt = rtt;
                   }
               }

          }
           if(didint) {
               double tmin = DBL_MAX;
               GeoObject *cur;
               for(QVector<GeoObject*>::iterator stt = _olist->begin(); stt != _olist->end(); ++stt) {
                   GeoObject *st = *stt;
                   if(!st->intPts().isEmpty() && rt.c() == st->intPts().last().c() && st->intPts().last().t() < tmin) {
                       tmin = st->intPts().last().t();
                       rt = st->intPts().last();
                       cur = st;
                   }
                }
                   glm::vec3 ints = rt.getIntPoint();
                   glm::vec3 s =  glm::normalize(_light.pos()-ints);
                   glm::vec3 v =  glm::normalize(_cam.e() - ints);
                   glm::vec3 n = rt.n();
                   glm::vec3 r = -s + (2*glm::dot(s,n)/glm::dot(n,n))*n;
                   double lit = 0;
                   bool hit = false;

                   for(QVector<GeoObject*>::iterator sttt = _olist->begin(); sttt != _olist->end(); ++ sttt){ //Shading
                       GeoObject *stt = *sttt;
                       double dif, spec;
                       if(stt->id() != cur->id()) {
                           Ray feeler(ints,(_light.pos()-ints),0.0);
                           if(stt->testFeelerInt(feeler)) {
                               dif = 0;
                               spec = 0;
                               hit = true;
                           } else {
                               hit = false;
                           }
                       }
                       if(!hit) {
                           dif = cur->diff()*(glm::max(0.0f,glm::dot(s,n)));
                           double specm = glm::pow(glm::max(0.0f,(glm::dot(r,v)/(glm::length(r)*glm::length(v)))),0.92f);
                         //  if(specm > 0)std::cout << specm << std::endl;
                           spec = cur->spec()*specm;
                       }
                       lit = spec+dif+0.3;
                   }
                   int red = glm::min(255,(int)(cur->color().red()*lit));
                   int green = glm::min(255,(int)(cur->color().green()*lit));
                   int blue = glm::min(255,(int)(cur->color().blue()*lit));
                   pixCol = QColor(red,green,blue);



           }
           int shiftedx = i - _sx/2;
           int shiftedy = j - _sy/2;
           if(shiftedx > 0 && shiftedx < 600 && shiftedy > 0 && shiftedy < 600)
               _pixels->operator [](shiftedx)[shiftedy] = pixCol;

        }

    }
}


/*
void Trace::run() {
    double uc = _cam.wWidth()*((2)/_sx - 1);
    double uv = _cam.wHeight()*((2)/_sy - 1);
    for(double i = -_sx/2; i < _sx/2; i += 0.2) {
        for(double j = -_sy/2; j < _sy/2; j += 0.2) {
            double x = i*uc;
            double y = j*uc;
            glm::vec3 e1(-_cam.near()*_cam.n().x,-_cam.near()*_cam.n().y,-_cam.near()*_cam.n().z);
            glm::vec3 e2(uc*_cam.u().x*x,uc*_cam.u().y*x,uc*_cam.u().z*x);
            glm::vec3 e3(uv*_cam.v().x*y,uv*_cam.v().y*y,uv*_cam.v().z*y);
            glm::vec3 dir = e1 + e2 + e3;
            dir = glm::normalize(dir);
            Ray rt(_cam.e(),dir,0.0);
            QColor pixCol = recursiveColor(rt,0);
            glm::vec3 ints = rt.getIntPoint();
            int shiftedx = (int)( ints.x*(_sx/2) + _sx/2);
            int shiftedy = (int)(ints.y*(_sy/2) + _sy/2);
            if(shiftedx > 0 && shiftedx < 600 && shiftedy > 0 && shiftedy < 600)
                _pixels->operator [](shiftedx)[shiftedy] = pixCol;


        }
    }
}

*/



//Get and set the pixel list
QVector<QVector<QColor> > *Trace::pixels() const
{
    return _pixels;
}

void Trace::setPixels(QVector<QVector<QColor> > *pixels)
{
    _pixels = pixels;
}
//Get and set the sphere list
QVector<Sphere> *Trace::slist() const
{
    return _slist;
}

void Trace::setSlist(QVector<Sphere> *slist)
{
    _slist = slist;
}
/*
QColor Trace::recursiveColor(Ray &rt,int depth)
{
    QColor results(255,255,255);
    if(depth < 4) {

        bool didint = false;
        for(QVector<Sphere>::iterator st = _slist->begin(); st != _slist->end(); ++st) {
            if(st->testIntersection(rt)) didint = true;
        }
        if(didint) {
            for(QVector<Sphere>::iterator st = _slist->begin(); st != _slist->end(); ++st) {
                rt = st->intPts().last();
                rt = MatrixOperations::scaleTransform(st->scale(),rt);
                rt = MatrixOperations::transTransform(st->trans(),rt);
                glm::vec3 ints = rt.getIntPoint();
                glm::vec3 s = glm::normalize(_light.pos()- ints);
                glm::vec3 v =  glm::normalize(_cam.e() - ints);
                glm::vec3 n = ints;
                glm::vec3 n2 = glm::normalize(n);
                glm::vec3 r = 2*(glm::dot(s,n2))*n2 - s;
                double lit = 0;
                double spec =0;
                for(QVector<Sphere>::iterator stt = _slist->begin(); stt != _slist->end(); ++ stt){ //Shadowing
                    double dif = st->diff()*(glm::max(0.0f,glm::dot(s,n2)));
                    spec = st->spec()*glm::pow(glm::max(0.0f,(glm::dot(r,v))),1.0f);
                    if(stt->id() != st->id()) {
                        Ray feeler(ints,s,0.0);
                        if(stt->testFeelerInt(feeler)) {
                            dif = 0;
                            spec = 0;
                        }
                    }
                    lit = dif+0.3;
                }
                int red,blue,green;
                red = blue = green = 0;
                if(spec != 0) {
                    Ray refRay(ints,r,0.0);
                    QColor recCol = recursiveColor(refRay,depth+1);
                     red = glm::min(255,(int)(st->color().red()*lit+recCol.red()*spec));
                     green = glm::min(255,(int)(st->color().green()*lit+recCol.green()*spec));
                     blue = glm::min(255,(int)(st->color().blue()*lit+recCol.blue()*spec));
                }
                else {
                     red = glm::min(255,(int)(st->color().red()*lit));
                     green = glm::min(255,(int)(st->color().green()*lit));
                     blue = glm::min(255,(int)(st->color().blue()*lit));
                }

                results = QColor(red,green,blue);


            }
        } else return QColor(255,255,255);
    }
    return results;
}
*/
//Get and set the light
Light Trace::light() const
{
    return _light;
}

void Trace::setLight(const Light &light) {
    _light = light;
}

QVector<Plane> *Trace::plist() const
{
    return _plist;
}

void Trace::setPlist(QVector<Plane> *plist)
{
    _plist = plist;
}








QVector<GeoObject *> *Trace::olist() const
{
    return _olist;
}

void Trace::setOlist(QVector<GeoObject *> *olist)
{
    _olist = olist;
}
