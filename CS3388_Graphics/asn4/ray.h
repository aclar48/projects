#ifndef RAY_H
#define RAY_H
#include <glm/glm.hpp>

using namespace glm;
class Ray
{
public:
    Ray();
    Ray(const vec3 &e,const vec3 &c,const double &t);


    vec3 e() const;
    void setE(const vec3 &e);

    vec3 c() const;
    void setC(const vec3 &c);

    double t() const;
    void setT(double t);

    vec3 getIntPoint() const;

    vec3 n() const;
    void setN(const vec3 &n);

private:

    vec3 _e;

    vec3 _n;
    vec3 _c;
    double _t;

};

#endif // RAY_H
