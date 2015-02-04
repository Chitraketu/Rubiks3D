#ifndef DRAWER_H
#define DRAWER_H 


#include "vec3f.h"
#include "GlActivity.h"
#include "matrix.h"

using namespace GlActivities;
using namespace scan;
using namespace std;

class drawer:public GlActivity{
private:
    Matrices *matrix;


public:
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
    Matrices perspectiveProj(Matrices& object,float zView,float zPrp);

      
    
};
#endif

