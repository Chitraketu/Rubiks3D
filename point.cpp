#include "point.h"
edge::edge(point p1,point p2){
	this->p1 = p1;
		this->p2 = p2;
		this->ptemp = p1;
		slope = (p2.y - p1.y)/(p2.x - p1.x);
		invSlope = 1/slope;
		zslope = (p2.y - p1.y)/(p2.z - p1.z);
	}
bool edge::nextXval(){
		(ptemp.x) += invSlope;
		(ptemp.y)++;
		(ptemp.z) += (1/zslope);
	}
void edge::showSlope(){
	cout<<invSlope<<endl;
}

