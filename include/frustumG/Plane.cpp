#include "plane.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Plane::Plane( Vector3 &v1,  Vector3 &v2,  Vector3 &v3) {

	set3Points(v1,v2,v3);
}


Plane::Plane() {}

Plane::~Plane() {}


void Plane::set3Points( Vector3 &v1,  Vector3 &v2,  Vector3 &v3) {


	Vector3 aux1, aux2;

	aux1 = v1 - v2;
	aux2 = v3 - v2;

	normal = aux2 * aux1;

	normal.normalize();
	point=v2;
	d = -(normal.dot(point));
}

void Plane::setNormalAndPoint(Vector3 &new_normal, Vector3 &new_point) {

	normal = new_normal;
	normal.normalize();
	d = -(normal.dot(new_point));
}

void Plane::setCoefficients(float a, float b, float c, float new_d) {

	// set the normal vector
	normal.set(a,b,c);
	//compute the lenght of the vector
	float l = normal.length();
	// normalize the vector
	normal.set(a/l,b/l,c/l);
	// and divide d by th length as well
	d = new_d/l;
}


	

float Plane::distance(Vector3 &p) {

	return (d + normal.dot(p));
}

void Plane::print() {

	//printf("Plane(");normal.print();printf("# %f)",d);
	cout<<"normal"<<endl;
}
