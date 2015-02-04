#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>

/*this is the base class
 * for the matrix 
 * manipulations like
 * assignments and the
 * multiplications purposes for the 
 * transformation
 */


class Matrices{
private:
    int row;
    int coloumn;
    float **mat;
public:
    /*this is the constructor
     * for this matrix 
     * base class
     */

    Matrices(int r,int c,bool ch=true);
    
    /*this is the internal 
     * class for the
     * double index 
     * operator overloading
     */
    
    class Proxy{
    private:
        float* _array;
    public:
	/*this is the internal 
	 * constructor
	 */

        Proxy(float* _array):_array(_array){}
	/* this is the internal 
	 * [] operator overloading 
	 * method
	 */

	float& operator[](int index);
	
    };

    /*external []
     * operator overloaded
     */

    Proxy operator[](int index);
    
    /*this is the method to 
     * get the row of the matrix
     */

    int getRow();

    /*this is the method to
     * get the coloumn of the matrix
     */

    int getColoumn();

    /*this is the * operator 
     * overloaded to multiply
     * two matrix if possible
     */

    Matrices operator*(Matrices& matrix);

    /*this is the = operator
     * overloaded to assign
     * if possible
     */

    void operator=(Matrices matrix);

    /*this is the mehtod
     * to display the matrix
     */

    void showmatrix();
};
#endif
