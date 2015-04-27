#ifndef FRUSTUMG_H_DEF
#define FRUSTUMG_H_DEF

#include <cmath>
#include <iostream>
#include "../matrix/src/Vectors.h"
#include "plane.h"


class FrustumG 
{
private:

	enum {
		TOP = 0,
		BOTTOM,
		LEFT,
		RIGHT,
		NEARP,
		FARP
	};


public:

	static enum Response{OUTSIDE, INTERSECT, INSIDE}x;

	Plane pl[6];


	Vector3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
	float nearD, farD, ratio, angle,tang;
	float nw,nh,fw,fh;

	FrustumG();
	~FrustumG();

	void setCamInternals(float new_angle, float new_ratio, float new_nearD, float new_farD);
	void setCamDef(Vector3 &p, Vector3 &l, Vector3 &u);
	int pointInFrustum(Vector3 &p);
	int sphereInFrustum(Vector3 &p, float ratio);
	//int boxInFrustum(AABox &b);

	void drawPoints();
	void drawLines();
	void drawPlanes();
	void drawNormals();
};


#endif
