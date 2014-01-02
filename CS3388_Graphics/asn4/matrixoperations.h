
/**
  Author: Alex Clarke
  Dec 06 2013
  
  Class containing the some matrix operations to make transformations easier
  */

#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ray.h"



#include <vector>
class MatrixOperations
{
public:
    MatrixOperations();

    static Ray &scaleTransform(const vec3 &vec, Ray &r);
    static Ray &transTransform(const vec3 &vec, Ray &r);
    static Ray &rotateXTransform(const float &deg,  Ray &r);
    static Ray &rotateYTransform(const float &deg,  Ray &r);
    static Ray &rotateZTransform(const float &deg, Ray &r);






private:



};

#endif // MATRIXOPERATIONS_H
