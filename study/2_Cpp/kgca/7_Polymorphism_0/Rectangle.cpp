#include "Rectangle.h"

void Rectangle::draw()
{
	cout << "Draw Rectangle : ";
	printf("(%d,%d)", x, y);
	printf("(%d*%d)", width, height);
	cout << endl;
}

void Rectangle::shape()
{
	cout << "Shape Rectangle : �簢��" << endl;
}


Rectangle::Rectangle()
{
	cout << "--------Rectangle ������" << endl;
}

Rectangle::Rectangle(int x, int y, int width, int height)
	:Figure(x, y, width, height)
{
	cout << "--------Rectangle ������" << endl;
}

Rectangle::~Rectangle()
{
	cout << "--------Rectangle �Ҹ���" << endl;
}
