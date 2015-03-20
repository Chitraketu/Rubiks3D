#include "drawCube.h"
drawCube::drawCube(){

		/*	cube[0][0]=0;
	cube[0][1]=10;
	cube[0][2]=10;
	cube[0][3]=0;
	cube[0][4]=0;
	cube[0][5]=0;
	cube[0][6]=10;
	cube[0][7]=10;
	cube[1][0]=0;
	cube[1][1]=0;
	cube[1][2]=10;
	cube[1][3]=10;
	cube[1][4]=10;
	cube[1][5]=0;
	cube[1][6]=0;
	cube[1][7]=10;
	cube[2][0]=0;
	cube[2][1]=0;
	cube[2][2]=0;
	cube[2][3]=0;
	cube[2][4]=10;
	cube[2][5]=1;
	cube[2][6]=10;
	cube[2][7]=10;
	cube[3][0]=10;
	cube[3][1]=10;
	cube[3][2]=10;
	cube[3][3]=10;
	cube[3][4]=10;
	cube[3][5]=10;
	cube[3][6]=10;
	cube[3][7]=1;*/
		face[0].p1 = point(0,0,0) ;
		face[0].p2 = point(0,20,0);
		face[0].p3 = point(0,20,20) ;
		face[0].p4 = point(0,0,20);

		face[1].p1 = point(20,0,0) ;
		face[1].p2 = point(20,20,0);
		face[1].p3 = point(20,20,20) ;
		face[1].p4 = point(20,0,20);
		
		face[2].p1 = point(0,0,0) ;
		face[2].p2 = point(0,0,20);
		face[2].p3 = point(20,0,20) ;
		face[2].p4 = point(20,0,0);
		
		face[3].p1 = point(0,20,0) ;
		face[3].p2 = point(0,20,20);
		face[3].p3 = point(20,20,20) ;
		face[3].p4 = point(20,20,0);
	
		face[4].p1 = point(0,0,0) ;
		face[4].p2 = point(0,20,0);
		face[4].p3 = point(20,20,0) ;
		face[4].p4 = point(20,0,0);
	
		face[5].p1 = point(0,0,20) ;
		face[5].p2 = point(0,20,20);
		face[5].p3 = point(20,20,20) ;
		face[5].p4 = point(20,0,20);

	}

vector<Matrices> drawCube::toMatrix(){
	for(int i =0;i<6;i++){
		Matrices mat(4,4,false);
		mat[0][0] = face[i].p1.x;
		mat[1][0] = face[i].p1.y;
		mat[2][0] = face[i].p1.z;
		mat[0][1] = face[i].p2.x;
		mat[1][1] = face[i].p2.y;
		mat[2][1] = face[i].p2.z;
		mat[0][2] = face[i].p3.x;
		mat[1][2] = face[i].p3.y;
		mat[2][2] = face[i].p3.z;
		mat[0][3] = face[i].p4.x;
		mat[1][3] = face[i].p4.y;
		mat[2][3] = face[i].p4.z;
		mat[3][0] = 1;
		mat[3][1] = 1;
		mat[3][2] = 1;
		mat[3][3] = 1;
		Matrix.push_back(mat);
	}
	return Matrix;
}
