#pragma once
#include "Figure.h"
class Rectangle : public Figure
{
public:
	void draw() override;      // �������̵�
//	void shape() override;     // �̷��� �������� ���.
	void shape();              // �������� �θ��� �޼ҵ尡 �����Լ��� �ƴϸ� override Ű���带 �� �� ����.
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	virtual ~Rectangle();
};

