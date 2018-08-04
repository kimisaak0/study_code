#include "Ellipse.h"
#include "Rectangle.h"
#include "Triangle.h"

int main()
{

	//�ڽ� Ŭ������ ���� ���� ����.
	Ellipse ellipse(30, 20, 50, 20);
	Triangle triangle(10, 10, 20, 30);
	Rectangle rectangle(20, 30, 10, 20);

	//Ŭ������ ��� �Լ��� ���� ȣ��
	ellipse.draw();
	ellipse.shape();
	triangle.draw();
	triangle.shape();
	rectangle.draw();
	rectangle.shape();

	const int FIGURE = 3; //�׳� ������ �ڽ� Ŭ������ ����� ����� ��

	//�θ�Ŭ������ �����ͷ� �ڽ� Ŭ������ �����Ҵ���. 
	Figure* figures[FIGURE] = {
		new Ellipse(10,10,20,30),
		new Triangle(20,30,10,20),
		new Rectangle(30,20,50,20)
	};

	//�θ� Ŭ���� �����ͷ� �ڽ� Ŭ������ ��� �Լ��� ��� ȣ��. 
	//�ڽ� Ŭ�������� �������� 
	for (int i = 0; i < FIGURE; i++) {
		figures[i]->draw();	  //�������� �θ��� �޼ҵ尡 �����Լ��� ���. �������� �ڽ��� �޼ҵ尡 ȣ���.
		figures[i]->shape();  //�������� �θ��� �޼ҵ尡 �����Լ��� �ƴ� ���. �θ��� �޼ҵ尡 ȣ���.
	}

	for (int i = 0; i < FIGURE; i++) {
		delete figures[i];
	}
}