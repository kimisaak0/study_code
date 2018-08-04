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
	cout << "Shape Ellipse : 타원" << endl;
}

Ellipse::Ellipse(int x, int y, int width, int height)
{
	move(x, y);
	resize(width, height);
	cout << "--------Ellipse 생성자" << endl;
}

Ellipse::Ellipse()
{
	cout << "--------Ellipse 생성자" << endl;
}


Ellipse::~Ellipse()
{
	cout << "--------Ellipse 소멸자" << endl;
}
