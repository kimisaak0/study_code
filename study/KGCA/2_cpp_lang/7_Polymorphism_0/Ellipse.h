#pragma once
#include "Figure.h"
class Ellipse : public Figure
{
public:
	void draw() override;		// override키워드 : 명시적으로 재정의한 함수임을 강조
	//void Draw() override;		// 이런식의 오타로 인한 실수를 방지할 수 있다.
	void shape();               // 재정의할 부모의 메소드가 가상함수가 아니면 override 키워드를 쓸 수 없다.
	//void shape() override;    // 이렇게 하면 빨간줄은 안 뜨는데 멤버 함수를 이미 정의했으니 에러가 뜬다.
public:
	Ellipse();
	Ellipse(int x, int y, int width, int height);
	virtual ~Ellipse();
};

