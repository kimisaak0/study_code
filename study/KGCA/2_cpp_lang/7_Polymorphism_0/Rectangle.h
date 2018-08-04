#pragma once
#include "Figure.h"
class Rectangle : public Figure
{
public:
	void draw() override;      // 오버라이딩
//	void shape() override;     // 이러면 빨간줄이 뜬다.
	void shape();              // 재정의할 부모의 메소드가 가상함수가 아니면 override 키워드를 쓸 수 없다.
public:
	Rectangle();
	Rectangle(int x, int y, int width, int height);
	virtual ~Rectangle();
};

