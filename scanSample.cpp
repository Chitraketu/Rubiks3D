#include <iostream>
#include<vector>

#include "scanLine.h"

using namespace std;
using namespace scan;
int main(){
	vector<edge*>Edges;
	cout<<"hello world"<<endl;
	float vert1[2]={1,2};
	float vert2[2]={3,1};
	float vert3[2]={5,3};
	edge* Edge;
	Edge =new edge(vert1,vert2);
	Edges.push_back(Edge);
	Edge =new edge(vert1,vert3);
	Edges.push_back(Edge);
	Edge =new edge(vert2,vert3);
	Edges.push_back(Edge);
	scanFill scans(Edges);
	scans.scanSort();
	scans.showEdges();

}

