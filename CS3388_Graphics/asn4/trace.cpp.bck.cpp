#include "trace.h"
#include "matrixoperations.h"
#include <iostream>
#define AMBIENT 0.4;

Trace::Trace():_pixels(new QVector<QVector<QColor> >())
{
}

Trace::Trace(const Camera &cam, const int &sx, const int &sy):_pixels(new QVector<QVector<QColor> >()), _slist(new QVector<Sphere>()), _plist(new QVector<Plane>())
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

Trace::~Trace()
{
    delete _pixels;
    delete _slist;
    delete _plist;
}
Camera Trace::cam() const
{
    return _cam;
}

void Trace::setCam(const Camera &cam)
{
    _cam = cam;
}

void Trace::run()
{
    //Sphere sp(0);

    //_slist->append(sp);
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
            bool didint = false;
            for(QVector<Sphere>::iterator st = _slist->begin(); st != _slist->end(); ++st) {

                bool didint = st->testIntersection(rt);
            }
            if(didint) {
                for(QVector<Sphere>::iterator st = _slist->begin(); st != _slist->end(); ++st) {

                    rt = MatrixOperations::scaleTransform(st->scale(),rt);
                    rt = MatrixOperations::transTransform(st->trans(),rt);
                    glm::vec3 ints = rt.getIntPoint();
                    int shiftedx = (int)( ints.x*(_sx/2) + _sx/2);
                    int shiftedy = (int)(ints.y*(_sy/2) + _sy/2);
                    glm::vec3 s = glm::normalize(_light.pos()- ints);
                    glm::vec3 v =  glm::normalize(_cam.e() - ints);
                    glm::vec3 n = ints;
                    glm::vec3 n2 = glm::normalize(n);
                    glm::vec3 r = 2*(glm::dot(s,n2))*n2 - s;
                    double lit = 0;

                    for(QVector<Sphere>::iterator stt = _slist->begin(); stt != _slist->end(); ++ stt){
                        double dif = st->diff()*(glm::dot(s,n2));
                        double spec = st->spec()*glm::pow(glm::max(0.0f,(glm::dot(r,v))),0.75f);
                        if(stt->id() != st->id()) {
                            Ray feeler(ints,s,0.0);
                            if(stt->testFeelerInt(feeler)) {
                               double dif = 0;
                               double spec = 0;

                            }
                        }
                       lit = spec+dif+0.3;
                    }

                     int red = glm::min(255,(int)(st->color().red()*lit));
                     int green = glm::min(255,(int)(st->color().green()*lit));
                     int blue = glm::min(255,(int)(st->color().blue()*lit));

                     if(shiftedx > 0 && shiftedx < 600 && shiftedy > 0 && shiftedy < 600)
                        _pixels->operator [](shiftedx)[shiftedy] = QColor(red,green,blue);

            }




}

          }
      }

}








    /*
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








            if(sp.testIntersection(rt)) {
               rt = MatrixOperations::scaleTransform(glm::vec3(0.3,0.3,1),rt);

                glm::vec3 ints = rt.getIntPoint();
                int shiftedx = (int)( ints.x*(_sx/2) + _sx/2);
                int shiftedy = (int)(ints.y*(_sy/2) + _sy/2);

                glm::vec3 s = _light.pos() - ints;
                glm::vec3 v = _cam.e() - ints;
                glm::vec3 n = ints;
                glm::vec3 r = -ints;

                double amb = 0.4;

                double dif = 0.3*(glm::dot(s,n));

                double spec = 0.7*(glm::dot(r,v));

                double lit = amb+dif+spec;

               _pixels->operator [](shiftedx)[shiftedy] = (QColor((int)(255*(lit)),(int)(255*(lit)),0));

               rt = MatrixOperations::transTransform(glm::vec3(0.75,-1.0,1),rt);
               rt = MatrixOperations::scaleTransform(glm::vec3(0.75,1,1),rt);
              ints = rt.getIntPoint();
               s = _light.pos() - ints;
               v = _cam.e() - ints;
               n = ints;
               r = -ints;

               Ray feeler(ints,_light.pos()-ints,0.0);
               if(sp.testFeelerInt(feeler)) {
                   dif = 0;
                   spec = 0;
               }
                lit = amb+dif+spec;




               shiftedx = (int)( ints.x*(_sx/2) + _sx/2);
               shiftedy = (int)(ints.y*(_sy/2) + _sy/2);
             //  std::cout << "t:" << rt.t() << std::endl;
               if(shiftedx >= 0 && shiftedx < _sx && shiftedy >= 0 && shiftedy < _sy)
               _pixels->operator [](shiftedx)[shiftedy] = (QColor((int)(255*(lit)),0,(int)(255*(lit))));
            }
            else {
               // _pixels->operator [](i).append(QColor(255,255,255));


            }

        }
    }
    */
            /*

    Sphere sp(_cam);
    for(QVector<Ray>::iterator rt = sp.intPts().begin(); rt != sp.intPts().end(); ++rt) {

        *rt = MatrixOperations::scaleTransform(glm::vec3(0.5,0.5,1),*rt);

         glm::vec3 ints = rt->getIntPoint();
        int shiftedx = (int)( ints.x*(_sx/2) + _sx/2);
      int shiftedy = (int)(ints.y*(_sy/2) + _sy/2);
     //  int shiftedx = ints.x;
     //   int shiftedy = ints.y;
         glm::vec3 s = _light.pos() - ints;
         glm::vec3 v = _cam.e() - ints;
         glm::vec3 n = ints;
         glm::vec3 r = -ints;

         double amb = 0.4;

         double dif = 0.3*(glm::dot(s,n));

         double spec = 0.7*(glm::dot(r,v));

         double lit = amb+dif+spec;
      //   _pixels->operator [](shiftedx)[shiftedy] = (QColor(255,0,0));
        _pixels->operator [](shiftedx)[shiftedy] = (QColor((int)(255*(lit)),(int)(255*(lit)),0));

    }

*/







QVector<QVector<QColor> > *Trace::pixels() const
{
    return _pixels;
}

void Trace::setPixels(QVector<QVector<QColor> > *pixels)
{
    _pixels = pixels;
}
QVector<Sphere> *Trace::slist() const
{
    return _slist;
}

void Trace::setSlist(QVector<Sphere> *slist)
{
    _slist = slist;
}




