#ifndef DRAWER_H
#define DRAWER_H 


#include "vec3f.h"
#include "GlActivity.h"
#include "matrix.h"
#include "point.h"
#include "drawCube.h"
#include<vector>
#include <iostream>
#include <cmath>
using namespace GlActivities;
using namespace std;
void plot(point P1,point P2);
void sorts(point& start, point& mid,point& end,const point P1, const point P2,const point P3);
void scanFill(point P1,point P2, point P3);
void fillFace(Matrices matrix,int color[4]);

Matrices translate(Matrices object,int x,int y,int z);
Matrices rotateX(Matrices objecect,float theta);
Matrices rotateY(Matrices objecect,float theta);
Matrices rotateZ(Matrices objecect,float theta);

class drawer:public GlActivity{
private:
    Matrices *matrix;


public:
    
	drawCube cubes;
	vector<Matrices>matrix1;
	drawer();
    /* this function is where the major rendering 
     * would be done
     * and all the rendering and shading 
     * algorithms would be called 
     * in this method
     */

    void display();
    /*this is the method to 
     * set up lookat point 
     * and transform it to 
     * origin and align it with 
     * the three-coordinate axes
     */

    Matrices lookAtPoint(Vec3f _eyeVector,Vec3f _eyeUp,Vec3f _lookAt);
    
    /*this is the method to 
     * generate the perspective projection
     */
    Matrices perspectiveProj(float fov,float aspect,float near,float far);
    static void drawLine(float vertexra,float vertexb,float yval);

      
    
};
#endif

