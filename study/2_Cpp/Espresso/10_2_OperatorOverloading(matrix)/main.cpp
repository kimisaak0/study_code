#include "matrix.h"

int main()
{
	
	matrix m1(2, 2); m1.setMat();
	matrix m2(2, 2); m2.setMat();
	matrix m3(1, 1); m3.setMat();

	cout << (m1 == m2) << endl;
	cout << (m1 != m3) << endl;
	
	cout << m1[01] << endl;
	cout << m3[00] << endl;
}