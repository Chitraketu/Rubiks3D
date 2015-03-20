#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/freeglut.h>
#include<iostream>
#include<cmath>
int db[500][500]={0};
using namespace std;
struct point{
	float x,y,z;
	point():x(0),y(0),z(0){}
	point(float xx,float yy,float zz):x(xx),y(yy),z(zz){}
};


struct edge{
	point p1,p2,ptemp;
	float slope;
	float invSlope;
	float zslope;
	edge(int vertex1[2],int vertex2[2]){
		p1.x = vertex1[0];
		p1.y = vertex1[1];
		p2.x = vertex2[0];
		p2.y = vertex2[1];
		slope = (p2.y - p1.y)/(p2.x - p1.x);
		invSlope = 1/slope;
		//cout<<slope<<'\t'<<invSlope;

		
	}
	edge(point p1,point p2){
		this->p1 = p1;
		this->p2 = p2;
		this->ptemp = p1;
		slope = (p2.y - p1.y)/(p2.x - p1.x);
		if(p2.x == p1.x)
			invSlope = 0;
		else
			invSlope = 1/slope;
		zslope = (p2.y - p1.y)/(p2.z - p1.z);
//		cout<<p1.x<<' '<<p1.y<<'\t'<<p2.x<<' '<<p2.y<<endl;

	}
	bool nextXval(){
		(ptemp.x) += invSlope;
		(ptemp.y)++;
		(ptemp.z) += (1/zslope);
//		cout<<ptemp.x<<"\t";
	}
	void showSlope(){
		cout<<invSlope<<endl;
	}
};
void plot(int x1,int x2,int y){
	int xsmall,xbig;
	glBegin(GL_POINTS);
	if(x1 <x2){
		xsmall = x1;
		xbig = x2;
	}
	else{
		xsmall = x2;
		xbig = x1;
	}
	for(int x = xsmall;x<=xbig;x++){
		glVertex2i(x,y);
	}
	glEnd();
}
void plot(point P1,point P2,int y){
	int xsmall,xbig;
	point psmall,pbig;
	glBegin(GL_POINTS);
	if(P1.x <P2.x){
		psmall = P1;
		pbig = P2;
	}
	else{
		psmall = P2;
		pbig = P1;
	}
	float zslope = (pbig.x - psmall.x)/(pbig.z - psmall.z); 
	int zval = psmall.z;
	float yval = psmall.y;
//	cout<<zslope<<endl;
	for(int i = psmall.x; i<=pbig.x; ++i){
		if(db[i][y]<zval){
			cout<<i<<'\t'<<zval<<endl;
			db[i][y] = zval;
			glVertex2i(i,yval);
			zval += (1/zslope);
		}else{
			cout<<i<<'\t'<<zval<<endl;
			cout<<zval<<endl;
			zval += (1/zslope);
			continue;
		}

	}
	glEnd();
}
int max(int x,int y,int z){
	float maxy;
	if(x>y && x >z)
		maxy= x;
	else if(y>z && y>x)
		maxy = y;
	return maxy;
}
void sorts(point& start,point& mid,point& end,const point P1,const point P2,const point P3){
	if(P1.y< P2.y && P1.y < P3.y){
		start = P1;
		if(P2.y < P3.y){
			mid = P2;
			end = P3;
		}else{
			mid = P3;
			end = P2;
		}
	}else if(P2.y <P1.y && P2.y < P3.y){
		start = P2;
		if(P1.y < P3.y){
			mid = P1;
			end = P3;
		}else{
			mid = P3;
			end = P1;
		}
	}else{
		start = P3;
		if(P1.y < P2.y){
			mid = P1;
			end = P2;
		}else{
			mid = P2;
			end = P3;
		}
	}
}
void scanFill(point P1,point P2,point P3){
	point start,mid,end;
	sorts(start,mid,end,P1,P2,P3);
	//cout<<endl;
	edge Elong(start,end);
	edge Epart1(start,mid);
	edge Epart2(mid,end);
	Elong.showSlope();
	Epart1.showSlope();
	Epart2.showSlope();
//	cout<<start.z<<endl;
	if(start.y == mid.y){
		edge Eparta(start,end);
		edge Epartb(mid,end);
		for(int i = start.y;i<= end.y;++i){
			plot(Eparta.ptemp,Epartb.ptemp,i);
			Eparta.nextXval();
			Epartb.nextXval();

		}
	}else if(start.y == end.y){
		plot(start,end,start.y);
	}else if(mid.y == end.y){
		edge Eparta(start,mid);
		edge Epartb(start,end);
		for(int i = start.y;i <= mid.y;++i){
			plot(Eparta.ptemp,Epartb.ptemp,i);
			Eparta.nextXval();
			cout<<"aah"<<Epartb.ptemp.x<<endl;
			Epartb.nextXval();
		}


	}else{
		for(int i = start.y;i<mid.y;++i){
//			plot(round(Epart1.ptemp.x),round(Elong.ptemp.x),i);
			plot(Epart1.ptemp,Elong.ptemp,i);
			Elong.nextXval();
			Epart1.nextXval();
		}
		for(int i = mid.y;i<end.y;i++){
		//	plot(round(Elong.ptemp.x),round(Epart2.ptemp.x),i);
			plot(Elong.ptemp,Epart2.ptemp,i);
			Elong.nextXval();
			Epart2.nextXval();
		}


	}


}

void displayWrapper(){
	for(int i =0;i<500;i++)
		for(int j =0;j<500;j++)
			db[i][j] = 0;
	glClearColor(0.0,0.0,0.0,0.0); 
	glClear(GL_COLOR_BUFFER_BIT);
	point *p1,*p2,*p3;
	p1 = new point(10,10,1);	
	p2 = new point(100,10,22);
	p3 = new point(100,100,3);
	     glMatrixMode(GL_PROJECTION);
		          glLoadIdentity();
		          gluOrtho2D(0.0, 500.0, 0.0, 500.0); 
	point p4(10,100,4);
	point p5(40,200,45);
	glColor4f(0.5f,0.2f,0.3f,1.0f);
	scanFill(*p3,*p1,p4);
	point p6(100,30,65);
	glColor4f(0.4f,0.9f,0.0f,1.0f);
	//scanFill(p4,p5,p6);
glutSwapBuffers();
}

int main(int argc,char** argv){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutCreateWindow("chitraketu");
	glutDisplayFunc(displayWrapper);
	glutMainLoop();
}
