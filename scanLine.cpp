#include"scanLine.h"
#include<iostream>
#include<vector>
#include <cmath>

using namespace std;
namespace scan{
    edge::edge(float vertex1[2],float vertex2[2]){
	this->vertex1[0]=vertex1[0];
	this->vertex1[1]=vertex1[1];	
	this->vertex2[0]=vertex2[0];	
	this->vertex2[1]=vertex2[1];
	slope = (vertex2[1]-vertex1[1])/(vertex2[0]-vertex1[0]);
	invSlope = 1/slope;
    }
    float edge::maxY(){
	return vertex2[1]>vertex1[1]?vertex2[1]:vertex1[1];
    }
    float edge::minY(){
	return vertex2[1]<vertex1[1]?vertex2[1]:vertex1[1];
    }
    float edge::xval(){
	return vertex2[1]<vertex1[1]?vertex2[0]:vertex1[0];
    }
    void edge::show(){
	    cout<<minY()<<'\t'<<maxY()<<'\t'<<xval()<<'\t'<<slope<<'\t'<<invSlope<<"Edge List"<<endl;
    }
    void GlobalEdge::show(){
	cout<<ymin<<'\t'<<ymax<<'\t'<<xval<<'\t'<<invSlope<<"Global Edge"<<endl;    
    }
    bool ActiveEdge::operator<(const ActiveEdge& actvEdg){
	    return xval < actvEdg.xval;
    }
}
using namespace scan;
scanFill::scanFill(vector<scan::edge*> E){
	
	EdgeList=E;
}
void scanFill::scanSort(){
    bool flag = false;
    vector<edge*>::iterator it;
     it = EdgeList.begin();
    (*it)->show();
    GlobalEdge* glEdge = new GlobalEdge((*it)->maxY(),(*it)->minY(),(*it)->xval(),(*it)->slope);
    vector<GlobalEdge*>::iterator GlItr;
    GlItr = sortedEdgeList.begin();
    sortedEdgeList.insert(GlItr,glEdge);
    it++;
    for(;it!=EdgeList.end();it++){
        (*it)->show();
        if((*it)->slope == 0)
            continue;
        GlobalEdge* glEdge = new GlobalEdge((*it)->maxY(),(*it)->minY(),(*it)->xval(),(*it)->slope);
        for(GlItr=sortedEdgeList.begin();GlItr!=sortedEdgeList.end();GlItr++){
            if((*GlItr)->ymin != (*it)->minY()){
                if((*GlItr)->ymin > (*it)->minY()){
                    sortedEdgeList.insert(GlItr,glEdge);
                    flag = true;
                    break;
                }
            }else if((*GlItr)->xval != (*it)->xval()){
                if((*GlItr)->xval > (*it)->xval()){
                    sortedEdgeList.insert(GlItr,glEdge);
                    flag = true;
                    break;
                }
            }else{
                if((*GlItr)->ymax > (*it)->maxY()){
                    sortedEdgeList.insert(GlItr,glEdge);
                    flag = true;
                    break;
                }
            }

            //cout<<(*GlItr)->ymax;
        }
        if(!flag){
            sortedEdgeList.push_back(glEdge);
        }
        flag = false;
    }
}
void scanFill::showEdges(){
	for(vector<scan::GlobalEdge*>::iterator it = sortedEdgeList.begin();it!=sortedEdgeList.end();it++){
		//(*it)->show();

	}
	//cout<<sortedEdgeList.size();

}
void scanFill::Fill(){
    bool flag = false;
    vector<float>xvals;
    float scanline = sortedEdgeList[0]->ymin;
    do{
	//initialization of Active Edge Table
	for(vector<GlobalEdge*>::iterator it=sortedEdgeList.begin();it!=sortedEdgeList.end();it++){
		if(fabs((*it)->ymin - scanline) <= 0.0001){
			(*it)->show();
			cout<<"active edge not fucking"<<endl;
			ActiveEdge* activeEdge = new ActiveEdge((*it)->ymax,(*it)->xval,(*it)->invSlope);
			ActiveEdgeList.push_back(activeEdge);
		}
	}	

	for(vector<ActiveEdge*>::iterator itr = ActiveEdgeList.begin();itr!=ActiveEdgeList.end();itr++){
	    xvals.push_back((*itr)->xval);
	    flag = flag?false:true;
	    if(!flag){
		    float x1 = xvals.back();
		    xvals.pop_back();
		    float x2 = xvals.back();
		    xvals.pop_back();
		drawer::drawLine(x1,x2,scanline);
	    }
	}
	scanline+=0.001;
	update();
	for(vector<ActiveEdge*>::iterator itr = ActiveEdgeList.begin();itr!=ActiveEdgeList.end();itr++){
	    if(fabs(scanline - (*itr)->ymax) < 0.001){
		    ActiveEdgeList.erase(itr);
		    itr++;
	    }
	}

	reOrderAET();

    }while(fabs(scanline - sortedEdgeList.back()->ymax) <= 0.001);
	    
}

void scanFill::reOrderAET(){
	sort(ActiveEdgeList.begin(),ActiveEdgeList.end());
}
void scanFill::update(){
for(vector<ActiveEdge*>::iterator itr = ActiveEdgeList.begin();itr!=ActiveEdgeList.end();itr++){
	(*itr)->xval+=(0.001*(*itr)->invSlope);
}	 
}
