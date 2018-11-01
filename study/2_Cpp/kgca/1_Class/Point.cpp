#include "Point.h"

void Point::SetPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}
void Point::Move(int _x, int _y)
{
	x += _x;
	y += _y;
}

void Point::Show(void)
{
	std::cout << "(" << x << "," << y << ")" << std::endl;
}

Point::Point()
{
	std::cout << "constuctor" << std::endl;
}


Point::~Point()
{
	std::cout << "dIstructor" << std::endl;
}
