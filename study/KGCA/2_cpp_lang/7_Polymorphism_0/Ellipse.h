#pragma once
#include "Figure.h"
class Ellipse : public Figure
{
public:
	void draw() override;		// overrideŰ���� : ��������� �������� �Լ����� ����
	//void Draw() override;		// �̷����� ��Ÿ�� ���� �Ǽ��� ������ �� �ִ�.
	void shape();               // �������� �θ��� �޼ҵ尡 �����Լ��� �ƴϸ� override Ű���带 �� �� ����.
	//void shape() override;    // �̷��� �ϸ� �������� �� �ߴµ� ��� �Լ��� �̹� ���������� ������ ���.
public:
	Ellipse();
	Ellipse(int x, int y, int width, int height);
	virtual ~Ellipse();
};

