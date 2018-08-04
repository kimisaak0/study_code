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
	cout << "Shape Triangle : �ﰢ��" << endl;
}

Triangle::Triangle()
{
	cout << "--------Triangle ������" << endl;
}

Triangle::Triangle(int x, int y, int width, int height)
	:Figure(x, y, width, height)
{
	cout << "--------Triangle ������" << endl;
}

Triangle::~Triangle()
{
	cout << "--------Triangle �Ҹ���" << endl;
}
