#include "Point.h"

int main()
{
	Point p1, p2;

	p1.SetPosition(10, 20);	//p1�� ��ǥ ����
	p2.SetPosition(50, 60); //p2�� ��ǥ ����

	p1.Move(5, 0);
	p2.Move(0, 5);

	p1.Show();
	p2.Show();

	return 0;
}