#ifndef AABOX_H_DEF
#define AABOX_H_DEF

#include "../matrix/src/Vectors.h"


class AABox 
{

public:

	Vector3 corner;
	float x,y,z;


	AABox( Vector3 &new_corner, float new_x, float new_y, float new_z);
	AABox();
	~AABox();

	void setBox( Vector3 &new_corner, float new_x, float new_y, float new_z);

	// for use in frustum computations
	Vector3 getVertexP(Vector3 &normal);
	Vector3 getVertexN(Vector3 &normal);


};


#endif
