#ifndef PLANE_H_DEF
#define PLANE_H_DEF
#include "../matrix/src/Vectors.h"


class Plane  
{

public:

	Vector3 normal,point;
	float d;


	Plane( Vector3 &v1,  Vector3 &v2,  Vector3 &v3);
	Plane();
	~Plane();

	void set3Points( Vector3 &v1,  Vector3 &v2,  Vector3 &v3);
	void setNormalAndPoint(Vector3 &new_normal, Vector3 &new_point);
	void setCoefficients(float a, float b, float c, float new_d);
	float distance(Vector3 &p);

	void print();

};


#endif
