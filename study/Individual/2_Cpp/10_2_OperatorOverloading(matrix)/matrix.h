#pragma once
#include "Header.h"


class matrix
{
private :
	int row;
	int column;
	int** number;

public:
	void setMat();
	void showMat();

	int getRow() { return row; }
	int getColumn() { return column; }

	matrix();
	matrix(int r, int c);
	matrix(const matrix &obj);


	bool operator==(const matrix& m2) const;
	bool operator!=(const matrix& m2) const;

	matrix operator+ (const matrix& m2);
	matrix operator- (const matrix& m2);
	matrix operator* (const matrix& m2);
//	matrix operator/ (matrix& v2);

	matrix operator* (int mag) const; // p2=p1*2;
	matrix operator/ (int div) const; // p2=p1/2;	

	friend matrix operator* (int mag, const matrix &pt); 
	friend matrix operator/ (int div, const matrix &pt); 

	matrix& operator=  (const matrix& m2);
	matrix& operator+= (const matrix& m2);
	matrix& operator-= (const matrix& m2);
	matrix& operator*= (int mag);
	matrix& operator/= (int div);

	int &operator[](int index);

	virtual ~matrix();
};

