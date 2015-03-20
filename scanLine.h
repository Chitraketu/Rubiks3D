#ifndef SCANLINE_H
#define SCANLINE_H

#include<iostream>
#include<vector>
#include<algorithm>
#include "drawer.h"
using namespace std;
namespace scan{
    struct edge{
	float vertex1[2];
        float vertex2[2];
	float slope; 
	float invSlope; 
	edge(float vertex1[2],float vertex2[2]);
	void show();
	float maxY();
	float minY();
	float xval();
    };
    struct GlobalEdge{
	float ymax;
	float ymin;
	float xval;
	float invSlope;
	GlobalEdge(float ymax,float ymin,float xva,float inv):ymax(ymax),ymin(ymin),xval(xva),invSlope(inv){}
	void show();
    
    };
    struct ActiveEdge{
	float ymax,xval,invSlope;    
	ActiveEdge(float _ymax,float _xval,float _invSlope):ymax(_ymax),xval(_xval),invSlope(_invSlope){}
	bool operator<(const ActiveEdge& actvEdg);
    };
}
    class scanFill{
    private:
	    vector<int>A;
	    vector<scan::edge*> EdgeList;
	    vector<scan::GlobalEdge*> sortedEdgeList;
	    vector<scan::ActiveEdge*> ActiveEdgeList;
    public:
	scanFill(vector<scan::edge*> E);
	void scanSort();
	void Fill();	
	void showEdges();
	void reOrderAET();
	void update();
    };
#endif
