#include "Ellipse.h"

void Ellipse::draw()
{
	cout << "Draw Ellipse : ";
	printf("(%d,%d)", x, y);
	printf("(%d*%d)", width, height);
	cout << endl;
}

void Ellipse::shape()
{
	cout << "Shape Ellipse : Ÿ��" << endl;
}

Ellipse::Ellipse(int x, int y, int width, int height)
{
	move(x, y);
	resize(width, height);
	cout << "--------Ellipse ������" << endl;
}

Ellipse::Ellipse()
{
	cout << "--------Ellipse ������" << endl;
}


Ellipse::~Ellipse()
{
	cout << "--------Ellipse �Ҹ���" << endl;
}
