#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
class Matrices{
private:
    int row;
    int coloumn;
    int **mat;
public:
    Matrices(int r,int c,bool ch=true);
    class Proxy{
    private:
        int* _array;
    public:
        Proxy(int* _array):_array(_array){}
	int& operator[](int index);
    };
    Proxy operator[](int index);
    int getRow();
    int getColoumn();
    Matrices operator*(Matrices& matrix);
    void operator=(Matrices& matrix);
    void showmatrix();
};
#endif
