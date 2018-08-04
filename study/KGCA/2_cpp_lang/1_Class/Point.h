#pragma once

#include <iostream>

class Point
{
private:
	int x, y;
public:
	void SetPosition(int _x, int _y);
	void Move(int _x, int _y);
	void Show(void);
	Point();
	~Point();
};

