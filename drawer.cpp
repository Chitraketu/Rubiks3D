#include "drawer.h"
using namespace std;
float db[500][500];
float theta = 0;

inline void refreshBuffer(){
	for(int i = 0;i<500;i++)
		for(int j=0;j<500;j++)
			db[i][j] = -9999;
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
	float zval = psmall.z;
	float yval = psmall.y;
//	cout<<zslope<<endl;
	for(int i = psmall.x; i<=pbig.x; ++i){
		if(i<0 || i>500 || y <0 || y>500){
			cout<<i<<endl;
			return;
		}

		if(db[i][y]<zval){
		//	cout<<i<<'\t'<<zval<<endl;
			db[i][y] = zval;
			glVertex2i(i,yval);
			zval += (1/zslope);
		}else{
		//	cout<<i<<'\t'<<zval<<endl;
		//	cout<<zval<<endl;
			zval += (1/zslope);
			continue;
		}

	}
	glEnd();
}

void fillFace(Matrices matrix,int color[4]){
	glColor4f(color[0]/(float)10,color[1]/10,color[2]/10,1);
	point p1(matrix[0][0],matrix[1][0],matrix[2][0]);
	point p2(matrix[0][1],matrix[1][1],matrix[2][1]);
	point p3(matrix[0][2],matrix[1][2],matrix[2][2]);
	point p4(matrix[0][3],matrix[1][3],matrix[2][3]);
/*	Vec3f pa(p1.x,p1.y,p1.z);
	Vec3f pb(p2.x,p2.y,p2.z);
	Vec3f pc(p3.x,p3.y,p3.z);
	Vec3f pd(p4.x,p4.y,p4.z);
	
	Vec3f ab = pb - pa;
	Vec3f ac = pc - pa;
	Vec3f ad = pd - pa;
	
	float abm = ab.magnitude();
	float acm = ac.magnitude();
	float adm = ad.magnitude();
	
	cout<<abm<<"abm"<<endl;
	cout<<acm<<"acm"<<endl;
	cout<<adm<<"adm"<<endl;
	if(abm > acm && abm > adm){
		cout<<"a";
		scanFill(p1,p2,p3);
		scanFill(p1,p2,p4);
	}else if(acm > abm && acm > adm){
		cout<<"b";
		cout<<p1.x<<'\t'<<p1.y<<'\t'<<p1.z<<"a"<<endl;
		scanFill(p1,p3,p2);
		scanFill(p1,p3,p4);
	}else if(adm > abm && adm > acm){
		cout<<"c";
		scanFill(p1,p4,p2);
		scanFill(p1,p4,p3);
	}*/

	cout<<p1.x<<" "<<p1.y<<" "<<p1.z<<endl;
	cout<<p2.x<<" "<<p2.y<<" "<<p2.z<<endl;
	cout<<p3.x<<" "<<p3.y<<" "<<p3.z<<endl;
       
	cout<<endl;	
	scanFill(p1,p2,p3);
	scanFill(p1,p3,p4);
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
			end = P1;
		}
	}
}

void scanFill(point P1,point P2,point P3){

	cout<<endl;
	cout<<P1.x<<" "<<P1.y<<endl;
	cout<<P2.x<<" "<<P2.y<<endl;
	cout<<P3.x<<" "<<P3.y<<endl;

	point start,mid,end;
	sorts(start,mid,end,P1,P2,P3);
	cout<<endl;
		cout<<start.x<<" "<<start.y<<endl;
		cout<<mid.x<<" "<<mid.y<<endl;
		cout<<end.x<<" "<<end.y<<endl;


	if(start.y == mid.y){
		edge Eparta(start,end);
		edge Epartb(mid,end);
cout<<"endl"<<endl;	
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
			//cout<<"aah"<<Epartb.ptemp.x<<'\t'<<Eparta.ptemp.x<<endl;
			Epartb.nextXval();
		}


	}else{
		edge Elong(start,end);
		edge Epart1(start,mid);
		edge Epart2(mid,end);
		//cout<<start.z<<endl;
		for(int i = start.y;i<mid.y;++i){
			plot(Epart1.ptemp,Elong.ptemp,i);
			Elong.nextXval();
			Epart1.nextXval();
		}
		for(int i = mid.y;i<end.y;i++){
			plot(Elong.ptemp,Epart2.ptemp,i);
			Elong.nextXval();
			Epart2.nextXval();
		}
	}
}

Matrices translate(Matrices object,int x,int y,int z){
	Matrices result(4,4,false);	
	result[0][3] = x;
	result[1][3] = y;
	result[2][3] = z;
	result[0][0] = 1;
	result[1][1] = 1;
	result[2][2] = 1;
	result[3][3] = 1;
	result = result * object;
	return result;
}

Matrices rotateX(Matrices object,float theta){
	Matrices result(4,4,false);
	result[0][0] = 1;
	result[1][1] = cos(theta*22/7*1/180);
	result[1][2] = -sin(theta*22/7*1/180);
	result[2][1] = sin(theta*22/7*1/180);
	result[2][2] = cos(theta*22/7*1/180);
	result[3][3] = 1;
	Matrices res = result*object;

	return result*object;
}
Matrices rotateY(Matrices object,float theta){
	Matrices result(4,4,false);
	result[1][1] = 1;
	result[0][0] = cos(theta*22/7*1/180);
	result[2][0] = -sin(theta*22/7*1/180);
	result[0][2] = sin(theta*22/7*1/180);
	result[2][2] = cos(theta*22/7*1/180);
	result[3][3] = 1;
	Matrices res = result*object;
	result.showmatrix();
	cout<<"hulio"<<endl;
	return result*object;
}
Matrices rotateZ(Matrices object,float theta){
	Matrices result(4,4,false);
	result[2][2] = 1;
	result[0][0] = cos(theta*22/7*1/180);
	result[0][1] = -sin(theta*22/7*1/180);
	result[1][0] = sin(theta*22/7*1/180);
	result[1][1] = cos(theta*22/7*1/180);
	result[3][3] = 1;
	return result*object;
}

drawer::drawer(){
	matrix = new Matrices(4,4,false);
	matrix1 = cubes.toMatrix();
}
void drawer::drawLine(float vertexa,float vertexb,float yval){
}


void drawer::display(){
	theta+=.1;
        //vector<Matrices>matrixa = cubes.toMatrix();
	cout<<matrix1.size()<<endl;
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0); 
     //   theta %=360;	
	Matrices test(4,4,false);
	test[0][0] = 10;
	test[1][0] = 10;
	test[2][0] = 14;
	test[3][0] = 1;
	test[0][1] = 20;
	test[1][1] = 10;
	test[2][1] = 14;
	test[3][1] = 1;
	test[0][2] = 20;
	test[1][2] = 20;
	test[2][2] = 14;
	test[3][2] = 1;
	test[0][3] = 10;
	test[1][3] = 20;
	test[2][3] = 14;
	test[3][3] = 1;
	glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
//	matrix1[0] = test;
//	matrix1[0].showmatrix();
//	cout<<endl;
	Matrices projection = perspectiveProj(45,16/9,2,1000);
//	projection.showmatrix();
//	cout<<endl;
//	Matrices matrix10 = projection*matrix1[5];
//	matrix10.showmatrix();
//	matrix1[0] = matrix10;
//	matrix1[0].showmatrix();
	for(int i = 0;i<matrix1.size();i++){
		//matrix1[i].showmatrix();

		refreshBuffer();

		Matrices matrix1i = rotateX(matrix1[i],theta);
		matrix1i = rotateY(matrix1i,theta);
		matrix1i = translate(matrix1i,90,90,10);
		matrix1i = projection*matrix1i;
//		matrix1[i] = matrix1i;
	//	test = translate(test,10,10,10);
	//	test = rotateX(test,theta);

//		matrix1i.showmatrix();
		int color[] = {i*3,2*i-1,2*i+2,1};
//		//test = projection*test;
		fillFace(matrix1i,color);
	       
	}
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
	//Matrices 
	cout<<endl;
	//matrice.showmatrix();
	//cout<<endl;
	return matrice*mat;
}

Matrices drawer::perspectiveProj(float fov,float aspect,float near,float far){
	Matrices persProj(4,4,false);
	fov = fov * 3.141592 / 180;
	float temp = 1.0f / tanf(0.5f * fov);
	float d = 1.0f / (far - near);
	persProj[0][0] = temp/aspect;
	persProj[1][1] = temp;
	persProj[2][2] = -(far + near) * d;
	persProj[2][3] = -(2*far*near)*d;
        persProj[3][2] = -1.0f;	
	return persProj;
}
