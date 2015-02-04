#include "drawer.h"
#include <iostream>
using namespace std;
drawer::drawer(){
	matrix = new Matrices(4,4,false);
}

void drawer::display(){
	Matrices cube(4,8,false);
	Matrices result(4,4,false);

	//cube
	cube[0][0]=0;
	cube[0][1]=1;
	cube[0][2]=1;
	cube[0][3]=0;
	cube[0][4]=0;
	cube[0][5]=0;
	cube[0][6]=1;
	cube[0][7]=1;
	cube[1][0]=0;
	cube[1][1]=0;
	cube[1][2]=1;
	cube[1][3]=1;
	cube[1][4]=1;
	cube[1][5]=0;
	cube[1][6]=0;
	cube[1][7]=1;
	cube[2][0]=0;
	cube[2][1]=0;
	cube[2][2]=0;
	cube[2][3]=0;
	cube[2][4]=1;
	cube[2][5]=1;
	cube[2][6]=1;
	cube[2][7]=1;
	cube[3][0]=1;
	cube[3][1]=1;
	cube[3][2]=1;
	cube[3][3]=1;
	cube[3][4]=1;
	cube[3][5]=1;
	cube[3][6]=1;
	cube[3][7]=1;
        Vec3f up(0.0f,1.0f,0.0f);
        Vec3f eyeVector(1.0f,1.0f,1.0f);
        Vec3f lookAt(0.0f,0.0f,0.0f);
	result = lookAtPoint(eyeVector,up,lookAt);	
	//result.showmatrix();
	cube = result*cube;
	//cube.showmatrix();
	cube = perspectiveProj(cube,-3,9);
	cube.showmatrix();
	glBegin(GL_LINES);
	    glVertex2f(cube[0][0]/(5*cube[3][0]),cube[1][0]/(5*cube[3][0]));
	    glVertex2f(cube[0][1]/(5*cube[3][1]),cube[1][1]/(5*cube[3][1]));  
	    glVertex2f(cube[0][2]/(5*cube[3][2]),cube[1][2]/(5*cube[3][2]));    		
	    glVertex2f(cube[0][3]/5/cube[3][3],cube[1][3]/5/cube[3][3]);    
	    glVertex2f(cube[0][4]/5/cube[3][4],cube[1][4]/5/cube[3][4]);    
	    glVertex2f(cube[0][5]/5/cube[3][5],cube[1][5]/5/cube[3][5]);    	  
       	    glVertex2f(cube[0][6]/5/cube[3][6],cube[1][6]/5/cube[3][6]);    
	    glVertex2f(cube[0][7]/5/cube[3][7],cube[1][7]/5/cube[3][7]);
	    glVertex2f(cube[0][4]/5/cube[3][4],cube[1][4]/5/cube[3][4]);
	    glVertex2f(cube[0][7]/5/cube[3][7],cube[1][7]/5/cube[3][7]);
	    glVertex2f(cube[0][2]/5/cube[3][2],cube[1][2]/5/cube[3][2]);
	    glVertex2f(cube[0][7]/5/cube[3][7],cube[1][7]/5/cube[3][7]);
	    glVertex2f(cube[0][3]/5/cube[3][3],cube[1][3]/5/cube[3][3]); 
	    glVertex2f(cube[0][0]/5/cube[3][0],cube[1][0]/5/cube[3][0]);
  	    glVertex2f(cube[0][5]/5/cube[3][5],cube[1][5]/5/cube[3][5]);
	glEnd();
	glBegin(GL_LINES); 
	     glVertex2f(cube[0][1]/5/cube[3][1],cube[1][1]/5/cube[3][1]);   
	     glVertex2f(cube[0][6]/5/cube[3][6],cube[1][6]/5/cube[3][6]);  
	glEnd();
	glutSwapBuffers();
}

Matrices drawer::lookAtPoint(Vec3f _eyeVector,Vec3f _eyeUp,Vec3f _lookAt){
	Matrices mat(4,4,false);
	Vec3f uzdash;
        Vec3f _eyeDistance = _lookAt	-_eyeVector  ;
	uzdash = _eyeDistance.normalize();
	Vec3f uxdash;
	//cout<<uzdash<<endl;
	uxdash = _eyeUp.cross(uzdash)/_eyeUp.magnitude();
	//cout<<uydash;
	Vec3f uydash = uzdash.cross(uxdash);
	//mat.showmatrix();
	//cout<<uxdash<<endl<<uydash<<endl<<uzdash<<endl;
	mat[0][0]=uxdash[0];
	mat[0][1]=uxdash[1];
	mat[0][2]=uxdash[2];
	mat[0][3]=0;
	
	mat[1][0]=uydash[0];	
	mat[1][1]=uydash[1];	
	mat[1][2]=uydash[2];	
	mat[1][3]=0;


	mat[2][0]=uzdash[0];
	mat[2][1]=uzdash[1];
	mat[2][2]=uzdash[2];
	mat[2][3]=0;

	mat[3][0]=0;
	mat[3][1]=0;
	mat[3][2]=0;	
	mat[3][3]=1;
	
	Matrices matrice(4,4,false);
	matrice[0][0]=1; 	
	matrice[1][1]=1;	
	matrice[2][2]=1;
	matrice[0][3]=-_eyeVector[0];
	matrice[1][3]=-_eyeVector[1];	
	matrice[2][3]=-_eyeVector[2];	
	matrice[3][3]=1;
	//mat.showmatrix();
	//Matrices 
	cout<<endl;
	//matrice.showmatrix();
	cout<<endl;
	return matrice*mat;
}

Matrices drawer::perspectiveProj(Matrices& object,float zView,float zPrp){
	Matrices persProj(4,4,false);
	float dp = zPrp-zView;
	persProj[0][0]=1;
	persProj[1][1]=1;	
	persProj[2][2]=zView/dp;	
	persProj[3][3]=-zPrp/dp;
	persProj[2][3]=-zView*zPrp/dp;
	persProj[3][2]=1/dp;	
	persProj.showmatrix();
	return persProj*object;
}
