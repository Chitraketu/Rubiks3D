#include<iostream>
#include<vector>
using namespace std;
struct edge{
    float vertex1[2],vertex2[2];
    float slope;
    edge(float vertexa[2],float vertexb[2]){
        vertex1[0]=vertexa[0];
        vertex1[1]=vertexa[1];
        vertex2[1]=vertexb[1];
        vertex2[0]=vertexb[0];
        slope = (vertex2[1]-vertex1[1])/(vertex2[0]-vertex1[0]);
    }
    float maxY(){
        return vertex2[1]>vertex1[1]?vertex2[1]:vertex1[1];
    }
    float minY(){
        return vertex2[1]<vertex1[1]?vertex2[1]:vertex1[1];
    }
    float xval(){
        if(maxY()!=minY())
            return vertex2[1]<vertex1[1]?vertex2[0]:vertex1[0];
         else
            return vertex2[0]<vertex1[0]?vertex2[0]:vertex1[0];
    }
    void show(){
        cout<<minY()<<'\t'<<maxY()<<'\t'<<xval()<<'\t'<<slope<<" edge"<<endl;
    }
};
struct GlobalEdge{
    float ymax,ymin,xval,invslope;
    GlobalEdge(float _ymax,float _ymin,float _xval,float _slope):ymax(_ymax),ymin(_ymin),xval(_xval),invslope(1/_slope){}
    void show(){
        cout<<ymin<<'\t'<<ymax<<'\t'<<xval<<'\t'<<invslope<<" global"<<endl;
    }

};
int main(){
    bool flag = false;
    vector<edge*>Edges;
    vector<GlobalEdge*>sortedEdgeList;
    vector<edge*>::iterator it;
    edge* Edge;
    float vec0[] = {10,10};
    float vec1[]={10,16};
    float vec2[] = {16,20};
    float vec3[]={28,10};
    float vec4[] = {28,16};
    float vec5[] = {22,10};
    Edge = new edge(vec0,vec1);
    Edges.push_back(Edge);
    Edge = new edge(vec1,vec2);
    Edges.push_back(Edge);
    Edge = new edge(vec2,vec3);
    Edges.push_back(Edge);
    Edge = new edge(vec3,vec4);
    Edges.push_back(Edge);
    Edge = new edge(vec4,vec5);
    Edges.push_back(Edge);
    Edge = new edge(vec5,vec0);
    Edges.push_back(Edge);
    //cout<<Edges.size()<<endl;
    it = Edges.begin();
    (*it)->show();
    GlobalEdge* glEdge = new GlobalEdge((*it)->maxY(),(*it)->minY(),(*it)->xval(),(*it)->slope);
    vector<GlobalEdge*>::iterator GlItr;
    GlItr = sortedEdgeList.begin();
    sortedEdgeList.insert(GlItr,glEdge);
    it++;
    for(;it!=Edges.end();it++){
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
    for(GlItr=sortedEdgeList.begin();GlItr!=sortedEdgeList.end();GlItr++){
        (*GlItr)->show();
    }
    cout<<sortedEdgeList.size()<<endl;
    return 0;
}
