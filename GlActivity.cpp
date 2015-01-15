#include"GlActivity.h"
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
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
    }

    void GlActivity::reshape( int w,int h){
        glViewport(0,0,(GLsizei) w,(GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
	    glOrtho(-1.5,1.5,-1.5*(GLfloat)h/(GLfloat)w,
	    1.5*(GLfloat)h/(GLfloat)w,-10.0,10.0);
 	else
	    glOrtho(-1.5,1.5,-1.5*(GLfloat)w/(GLfloat)h,
	    1.5*(GLfloat)w/(GLfloat)h,-10.0,10.0);
	    glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();
    }

    void GlActivity::idle(){}

    void GlActivity::setInstance(){
        instance  = this;
    }

    void GlActivity::start(int argc,char** argv){
        setInstance();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE |GLUT_DEPTH);
	//glutInitWindowPosition(500,500);
	glutInitWindowSize(500,500);
	glutCreateWindow("chitraketu");
	glutReshapeFunc(reshapeWrapper);
	glutDisplayFunc(displayWrapper);
	init();
	glutIdleFunc(idleWrapper);
        glutKeyboardFunc(keydownWrapper);
	glutKeyboardUpFunc(keyupWrapper);	
	glutMainLoop();
    }


    void GlActivity::init(){
       glClearColor(0.0, 0.0, 0.0, 0.0);	
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
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
