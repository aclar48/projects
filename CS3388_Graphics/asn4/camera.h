#ifndef CAMERA_H
#define CAMERA_H
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    Camera(const glm::vec3 &e, const glm::vec3 &g, const glm::vec3 &p, const double &near, const double &aspect);

    glm::vec3 u() const;
    void setU(const glm::vec3 &u);

    glm::vec3 v() const;
    void setV(const glm::vec3 &v);

    glm::vec3 n() const;
    void setN(const glm::vec3 &n);

    glm::vec3 e() const;
    void setE(const glm::vec3 &e);

    double near() const;
    void setNear(double near);

    double wHeight() const;
    void setWHeight(double wHeight);

    double wWidth() const;
    void setWWidth(double wWidth);

private:
    glm::vec3 _u;
    glm::vec3 _v;
    glm::vec3 _n;
    glm::vec3 _e;
    double _near;
    double _wHeight;
    double _wWidth;


};

#endif // CAMERA_H
