#pragma once
#include <iostream>

class Tpoint
{
private:
	int x;
	int y;

public:
	void SetPosition(int i, int j);
	void Move(int i, int j);
	void Show();

public:
	Tpoint();
	~Tpoint();
};

