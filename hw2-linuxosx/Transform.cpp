// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
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

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  eye = rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  vec3 newAxis = glm::cross(eye, up);
  newAxis = glm::normalize(newAxis);

  eye = eye * rotate(degrees, newAxis);
  up = up * rotate(degrees, newAxis);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  mat4 ret = glm::lookAt(eye,center,up);

  return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  //std::cout<<"entrada" <<sx<< "-" << sy << "-" << sz << "-"<<std::endl;

  mat4 identity = mat4(1.0f);//identity matrix
  identity[0][0] = sx;
  identity[1][1] = sy;
  identity[2][2] = sz;

  mat4 ret = identity;
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 identity = mat4(1.0f);
  identity[0][3] = tx;
  identity[1][3] = ty;
  identity[2][3] = tz;
  mat4 ret = identity;
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
