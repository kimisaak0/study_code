#include "Tpoint.h"

void Tpoint::SetPosition(int i, int j)
{
	x = i;
	y = j;
}

void Tpoint::Move(int i, int j)
{
	x += i;
	y += j;
}

void Tpoint::Show()
{
	std::cout << x << " " << y << std::endl;
}


Tpoint::Tpoint()
{
	x = 0;
	y = 0;
}


Tpoint::~Tpoint()
{
	std::cout << "~Tpoint" << std::endl;
}
