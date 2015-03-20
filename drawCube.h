#ifndef DRAWCUBE_H
#define DRAWCUBE_H
#include "point.h"
#include<vector>
#include "matrix.h"
using namespace std;
struct faces{
	point p1,p2,p3,p4;
};
class drawCube{
private:
	faces face[6];
	vector<Matrices> Matrix;
public:
	drawCube();
	vector<Matrices> toMatrix();
	
};
#endif
