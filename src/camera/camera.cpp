#include "camera.h"
#include <stdio.h>
#include <iostream>
using namespace std;


Camera::Camera()
{
    x=0.0;
    y=0.0;
    z=0.0;
    lx=0.0;
    ly=0.0;
    lz=0.0;
    angle=0.0;
}

Camera::Camera(float new_x,float new_y,float new_z,
           float newLookAt_x, float newLookAt_y, float newLookAt_z,
           float newAngle,float new_near, float new_far,float new_FOV)
{
    x = new_x;
    y = new_y;
    z = new_z;
    lx=newLookAt_x;
    ly=newLookAt_y;
    lz=newLookAt_z;
    angle=newAngle;
    near = new_near;
    far = new_far;
    FOV = new_FOV;
}

float Camera::getPos_x()
{
  return x;
}

float Camera::getPos_y()
{
  return y;
}

float Camera::getPos_z()
{
  return z;
}

float Camera::getLookAtPos_x()
{
  return lx;
}

float Camera::getLookAtPos_y()
{
  return ly;
}

float Camera::getLookAtPos_z()
{
  return lz;
}

float Camera::getCameraAngle()
{
  return angle;
}

float Camera::getNearPlane()
{
 return near;
}

float Camera::getFarPlane()
{
 return far;
}

float Camera::getFOV()
{
  return FOV;
}

float Camera::getAspect()
{
  return aspect;
}

void Camera::setAspect(float new_aspect)
{
  aspect = new_aspect;
}

void Camera::setPos_x(float new_x)
{
  x = new_x;
}

void Camera::setPos_y(float new_y)
{
  y = new_y;
}

void Camera::setPos_z(float new_z)
{
  z = new_z;
}  

void Camera::setNearPlane(float new_near)
{
  near = new_near;
}

void Camera::setFarPlane(float new_far)
{
  far = new_far;
}

void Camera::setFOV(float new_FOV)
{
  FOV = new_FOV;
}
  
void Camera::setLookAtPos_x(float newLookAt_x)
{
  lx = newLookAt_x;
}

void Camera::setLookAtPos_y(float newLookAt_y)
{
  ly = newLookAt_y;
}

void Camera::setLookAtPos_z(float newLookAt_z)
{
  lz = newLookAt_z;
}

void Camera::setCameraAngle(float newAngle)
{
  angle = newAngle;
}  
  

