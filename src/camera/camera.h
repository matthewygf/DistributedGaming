#ifndef CAMERA_H
#define CAMERA_H


using namespace std;

class Camera
{
    public:
    Camera();
    Camera(float new_x, float new_y, float new_z,
           float newLookAt_x, float newLookAt_y, float newLookAt_z,
           float newAngle);
    
    //getters
    float getPos_x();
    float getPos_y();
    float getPos_z();
    float getLookAtPos_x();
    float getLookAtPos_y();
    float getLookAtPos_z();
    float getCameraAngle();
    
    //setters
    void setPos_x(float new_x);
    void setPos_y(float new_y);
    void setPos_z(float new_z);
    void setLookAtPos_x(float newLookAt_x);
    void setLookAtPos_y(float newLookAt_y);
    void setLookAtPos_z(float newLookAt_z);
    void setCameraAngle(float newAngle);
    
    private:
    float x,y,z;
    float lx,ly,lz;
    float angle;

};
#endif
