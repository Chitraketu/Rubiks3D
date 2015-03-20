#include"GlActivity.h"
#include <iostream>
using namespace std;
namespace GlActivities {
    GlActivity *GlActivity::instance = NULL;
    
    GlActivity::GlActivity(){}

    void GlActivity::keydown(unsigned char ch,int x,int y){
        if(ch == 27) glutExit();
	keys[ch]=true;
    }

    void GlActivity::keyup(unsigned char ch,int x,int y){
        keys[ch]=false;
    }

    void GlActivity::display(void){
    }

    void GlActivity::reshape( int w,int h){
	    
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    }

    void GlActivity::idle(){
	    glutPostRedisplay();
    }

    void GlActivity::setInstance(){
        instance  = this;
    }

    void GlActivity::start(int argc,char** argv){
        setInstance();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//glutInitWindowPosition(500,500);
	glutInitWindowSize(500,500);
	glutCreateWindow("chitraketu");
	glutDisplayFunc(displayWrapper);
	init();

//glutPostRedisplay();	glutIdleFunc(idleWrapper);
	glutReshapeFunc(reshapeWrapper);
        glutKeyboardFunc(keydownWrapper);
	glutKeyboardUpFunc(keyupWrapper);	
	glutIdleFunc(idleWrapper);
	glutMainLoop();
    }


    void GlActivity::init(){
      // glClearColor(0.h, 0.0, 0.0, 1.0);	
      // glClear(GL_COLOR_BUFFER_BIT);
    }

    void GlActivity::displayWrapper(){
        instance->display();
    } 

    void GlActivity::reshapeWrapper(int w,int h){
        instance->reshape(w,h);
    }

    void GlActivity::idleWrapper(){
        instance->idle();
    }

    void GlActivity::keydownWrapper(unsigned char ch,int x,int y){
        instance->keydown(ch,x,y);
    }

    void GlActivity::keyupWrapper(unsigned char ch,int x,int y){
        instance->keyup(ch,x,y);
    }


    
}
