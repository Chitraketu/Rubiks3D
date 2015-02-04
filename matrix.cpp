#include "matrix.h"
#include <cstdio>
using namespace std;
Matrices::Matrices(int r,int c,bool ch){
    row = r;
    coloumn = c;
    mat = new float*[row];
    for(int i = 0;i < row;++i)
        for(int j = 0;j<coloumn;++j)
            mat[i]=new float[coloumn];
    if(ch){
        cout<<"enter the values of the matrix"<<endl;
	for(int i = 0;i < row;++i)
	    for(int j = 0;j < coloumn;++j)
		    cin>>mat[i][j];
    }else{
	for(int i =0;i<row;++i)
	    for(int j =0;j<coloumn;++j)
		mat[i][j]=0;
    }
}
float& Matrices::Proxy::operator[](int index){
    return _array[index];
}

Matrices::Proxy Matrices::operator[](int index){
   return Proxy(mat[index]);
}
int Matrices::getRow(){
   return row;
}
int Matrices::getColoumn(){
    return coloumn;
}
Matrices Matrices::operator*(Matrices& matrix){
    int l = matrix.getColoumn();
    Matrices result(row,l,false);
    for(int i=0;i < row;++i){
	for(int j = 0;j<l;++j){
	    result[i][j]=0;
	    for(int k = 0;k < coloumn;++k){
	        result[i][j]+=(mat[i][k]*matrix[k][j]);
	    }
        }
    }
    return result;
}
void Matrices::operator=(Matrices matrix){
    if(row!=matrix.getRow() && coloumn != matrix.getColoumn()){
	cout<<"can't assign"<<endl;
	return;
    }
    for(int i = 0;i < row;++i){
        for(int j = 0;j < coloumn;++j){
            this->mat[i][j]=matrix[i][j];
        }
    }
}
void Matrices::showmatrix(){
    for(int i = 0;i<row;++i){
	for(int j =0;j<coloumn;++j){
		printf("%-5.7f ",mat[i][j]);
	}
	cout<<endl;
    }
}    

