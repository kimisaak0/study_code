#pragma once
#include "Figure.h"
class Triangle : public Figure
{
public:
	void draw() override;     //�������̵�
	void shape(); 
public:
	Triangle();
	Triangle(int x, int y, int width, int height);
	virtual ~Triangle();
};

