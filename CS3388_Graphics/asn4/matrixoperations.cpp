
/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the some matrix operations to make transformations easier
  */

#include "matrixoperations.h"

MatrixOperations::MatrixOperations()
{
}
// Scale a ray given a vector
Ray &MatrixOperations::scaleTransform(const vec3 &vec, Ray &r)
{

    if(vec.x == 1.0 && vec.y == 1.0 && vec.z == 1.0) return r;
    mat4 *scaleMatrix = new mat4(1.0);
    *scaleMatrix = glm::scale(*scaleMatrix,vec);
    *scaleMatrix = inverse(*scaleMatrix);
    vec4 e(r.e(),1.0);
    vec4 c(r.c(),0.0);
    vec4 tempe = (*scaleMatrix*e);
    vec4 tempc = glm::normalize(*scaleMatrix*c);
    vec4 n(r.n(),0.0);
    vec4 tempn = (glm::transpose(*scaleMatrix)*n);
    vec3 newn(tempn.x,tempn.y,tempn.z);

    vec3 newe(tempe.x,tempe.y,tempe.z);
    vec3 newc(tempc.x,tempc.y,tempc.z);

    Ray *results = new Ray(newe,newc,r.t());
    results->setN(newn);
    return *results;


}
// Transform a ray given a vector
Ray &MatrixOperations::transTransform(const vec3 &vec,Ray &r)
{
    if(vec.x == 0 && vec.y == 0 && vec.z == 0)return r;
    mat4 *scaleMatrix = new mat4(1.0);
    *scaleMatrix = glm::translate(*scaleMatrix,vec);
    *scaleMatrix = inverse(*scaleMatrix);
    vec4 e(r.e(),1.0);
    vec4 c(r.c(),0.0);
    vec4 tempe = (*scaleMatrix*e);
    vec4 tempc = glm::normalize(*scaleMatrix*c);
    vec4 n(r.n(),0.0);
    vec4 tempn = (glm::transpose(*scaleMatrix)*n);

    vec3 newn(tempn.x,tempn.y,tempn.z);

    vec3 newe(tempe.x,tempe.y,tempe.z);
    vec3 newc(tempc.x,tempc.y,tempc.z);

    Ray *results = new Ray(newe,newc,r.t());
    results->setN(newn);

    return *results;
}
//Rotate along x
Ray &MatrixOperations::rotateXTransform(const float &deg, Ray &r)
{
    if(deg == 0) return r;
    mat4 *scaleMatrix = new mat4(1.0);
    *scaleMatrix = glm::rotate(*scaleMatrix,deg,glm::vec3(1,0,0));

    *scaleMatrix = inverse(*scaleMatrix);
    vec4 e(r.e(),1.0);
    vec4 c(r.c(),0.0);
    vec4 tempe = glm::normalize(*scaleMatrix*e);
    vec4 tempc = (*scaleMatrix*c);
    vec4 n(r.n(),0.0);
    vec4 tempn = (*scaleMatrix*n);
    vec3 newn(tempn.x,tempn.y,tempn.z);

    vec3 newe(tempe.x,tempe.y,tempe.z);
    vec3 newc(tempc.x,tempc.y,tempc.z);

    Ray *results = new Ray(newe,newc,r.t());
    results->setN(newn);

    return *results;
}
//Rotate along y
Ray &MatrixOperations::rotateYTransform(const float &deg, Ray &r)
{
    if(deg == 0) return r;
    mat4 *scaleMatrix = new mat4(1.0);
    *scaleMatrix = glm::rotate(*scaleMatrix,deg,glm::vec3(0,1,0));
    *scaleMatrix = inverse(*scaleMatrix);
    vec4 e(r.e(),1.0);
    vec4 c(r.c(),0.0);
    vec4 tempe = glm::normalize(*scaleMatrix*e);
    vec4 tempc = (*scaleMatrix*c);
    vec4 n(r.n(),0.0);
    vec4 tempn = (*scaleMatrix*n);
    vec3 newn(tempn.x,tempn.y,tempn.z);

    vec3 newe(tempe.x,tempe.y,tempe.z);
    vec3 newc(tempc.x,tempc.y,tempc.z);

    Ray *results = new Ray(newe,newc,r.t());
    results->setN(newn);

    return *results;
}
//Rotate along z
Ray &MatrixOperations::rotateZTransform(const float &deg, Ray &r)
{
    if(deg == 0) return r;
    mat4 *scaleMatrix = new mat4(1.0);
    *scaleMatrix = glm::rotate(*scaleMatrix,deg,glm::vec3(0,0,1));
    *scaleMatrix = inverse(*scaleMatrix);
    vec4 e(r.e(),1.0);
    vec4 c(r.c(),0.0);
    vec4 tempe = glm::normalize(*scaleMatrix*e);
    vec4 tempc = (*scaleMatrix*c);
    vec4 n(r.n(),0.0);
    vec4 tempn = (*scaleMatrix*n);
    vec3 newn(tempn.x,tempn.y,tempn.z);

    vec3 newe(tempe.x,tempe.y,tempe.z);
    vec3 newc(tempc.x,tempc.y,tempc.z);

    Ray *results = new Ray(newe,newc,r.t());
    results->setN(newn);

    return *results;
}


