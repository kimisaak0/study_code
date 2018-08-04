#include "Triangle.h"

void Triangle::draw()
{
	cout << "Draw triangle : ";
	printf("(%d,%d)", x, y);
	printf("(%d*%d)", width, height);
	cout << endl;
}

void Triangle::shape()
{
	cout << "Shape Triangle : 삼각형" << endl;
}

Triangle::Triangle()
{
	cout << "--------Triangle 생성자" << endl;
}

Triangle::Triangle(int x, int y, int width, int height)
	:Figure(x, y, width, height)
{
	cout << "--------Triangle 생성자" << endl;
}

Triangle::~Triangle()
{
	cout << "--------Triangle 소멸자" << endl;
}
