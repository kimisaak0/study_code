#include "Ellipse.h"
#include "Rectangle.h"
#include "Triangle.h"

int main()
{

	//자식 클래스를 각각 따로 선언.
	Ellipse ellipse(30, 20, 50, 20);
	Triangle triangle(10, 10, 20, 30);
	Rectangle rectangle(20, 30, 10, 20);

	//클래스의 멤버 함수를 각각 호출
	ellipse.draw();
	ellipse.shape();
	triangle.draw();
	triangle.shape();
	rectangle.draw();
	rectangle.shape();

	const int FIGURE = 3; //그냥 선언할 자식 클래스가 몇개인지 명시한 것

	//부모클래스의 포인터로 자식 클래스를 동적할당함. 
	Figure* figures[FIGURE] = {
		new Ellipse(10,10,20,30),
		new Triangle(20,30,10,20),
		new Rectangle(30,20,50,20)
	};

	//부모 클래스 포인터로 자식 클래스의 멤버 함수를 모두 호출. 
	//자식 클래스에서 재정의한 
	for (int i = 0; i < FIGURE; i++) {
		figures[i]->draw();	  //재정의한 부모의 메소드가 가상함수인 경우. 재정의한 자식의 메소드가 호출됨.
		figures[i]->shape();  //재정의한 부모의 메소드가 가상함수가 아닌 경우. 부모의 메소드가 호출됨.
	}

	for (int i = 0; i < FIGURE; i++) {
		delete figures[i];
	}
}