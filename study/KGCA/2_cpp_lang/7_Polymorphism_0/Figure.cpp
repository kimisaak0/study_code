#include "Figure.h"

void Figure::move(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Figure::resize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void Figure::draw()
{
	cout << "Figure : Draw" << endl;
}

void Figure::shape()
{
	cout << "Figure : shape" << endl;
}

Figure::Figure(int x, int y, int width, int height)
{
	move(x, y);
	resize(width, height);
	cout << "--------Figure 持失切" << endl;
}

Figure::Figure()
{
	cout << "--------Figure 持失切" << endl;
}

Figure::~Figure()
{
	cout << "--------Figure 社瑚切" << endl;
}
