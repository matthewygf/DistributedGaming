#ifndef CAMERA_H
#define CAMERA_H


using namespace std;

class Camera
{
    public:
    Camera();
    Camera(float new_x, float new_y, float new_z,
           float newLookAt_x, float newLookAt_y, float newLookAt_z,
           float newAngle,float new_near, float new_far,float new_FOV);
    
    //getters
    float getPos_x();
    float getPos_y();
    float getPos_z();
    float getLookAtPos_x();
    float getLookAtPos_y();
    float getLookAtPos_z();
    float getCameraAngle();
    float getNearPlane();
    float getFarPlane();
    float getFOV();
    float getAspect();
    
    //setters
    void setPos_x(float new_x);
    void setPos_y(float new_y);
    void setPos_z(float new_z);
    void setNearPlane(float new_near);
    void setFarPlane(float new_far);
    void setFOV(float new_FOV);
    void setAspect(float new_aspect);
    void setLookAtPos_x(float newLookAt_x);
    void setLookAtPos_y(float newLookAt_y);
    void setLookAtPos_z(float newLookAt_z);
    void setCameraAngle(float newAngle);
    
    private:
    float x,y,z;
    float lx,ly,lz;
    float angle;
    float near,far,FOV;
    float aspect;

};
#endif
