// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  float radians = degrees * M_PI / 180.0f;
    mat3 r1(cos(radians));
    mat3 r2(0, -axis.z, axis.y, 
            axis.z, 0, -axis.x, 
            -axis.y, axis.x, 0);
    mat3 r3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
            axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
            axis.x*axis.z, axis.z*axis.y, axis.z*axis.z);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            r2[i][j] = r2[i][j]*sin(radians);
            r3[i][j] = r3[i][j]*(1-cos(radians));
        }
    }
    return r1 + r2 + r3;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  eye = rotate(degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
  vec3 newAxis = glm::cross(eye, up);
  newAxis = glm::normalize(newAxis);

  eye = eye * rotate(degrees, newAxis);
  up = up * rotate(degrees, newAxis);
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
  vec3 center(0.0,0.0,0.0);

  mat4 mv = glm::lookAt(eye,center,up);

  return mv;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
