
#ifndef POINT_H
#define POINT_H
#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/freeglut.h>
using namespace std;
struct point{
	float x,y,z;
	point(float xx,float yy,float zz):x(xx),y(yy),z(zz){}
	point():x(0),y(0),z(0){}
};
struct edge{
	point p1,p2,ptemp;
	float slope;
	float invSlope;
	float zslope;
	edge(point p1,point p2);
	bool nextXval();
	void showSlope();
};
#endif
