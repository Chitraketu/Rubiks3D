#ifndef GLACTIVITY_H
#define GLACTIVITY_H

#include<GL/freeglut.h>
#include<GL/gl.h>

/**GlActivity.h
 * The GlActivity defines the super class that can be used to initialize
 * the glut and call the glut callback functions
 * which can be overridden or can be used directly
 */
namespace GlActivities{
class GlActivity{
protected:
    bool keys[256];
    static GlActivity* instance;
public:
    /*Initialize material property,light source,lighting model
     *and depth buffer through the constructor call.
     */
    GlActivity();
    virtual void keydown(unsigned char ch,int x,int y);
    
    /** The keydown function is to check 
    * if any key is pressed down or not.
    * This member function can be overridden to make the function 
    * do other tasks.
    */

    virtual void keyup(unsigned char ch,int x,int y);
    
    /** this is the similar function as
    * that of keydown
    */

    virtual void display(void);
    
    /** this is the main 
    * rendering function in order to
    * display.
    * The major portion of drawing are 
    * done by overriding this function
    */

    virtual void reshape(int w,int h);
    
    /* this is the reshape function
    * used when someone changes the size of the window
    */

    virtual void idle();
    
    /*this is the idle function which is
    * called during the idle state of the rendering
    * This method can be overridden to as per the need 
    * of the program
    */

    void setInstance();
    /**this the function to instantiate 
    * the GlActivity pointer type object instance 
    * with 'this'
    */

    void start(int arc,char** argv);

    /*this is the starting point of the glut
    * from here the rendering is started
    */

    void init();
    /**this function is for the initialization of 
    * the basic things of the OpenGl
    */

    //static functions which are passed to GLUT functions callbacks

    static void displayWrapper();
    static void reshapeWrapper(int w,int h);
    static void idleWrapper();
    static void keydownWrapper(unsigned char ch,int x,int y);
    static void keyupWrapper(unsigned char ch,int x,int y);

};
}
#endif
