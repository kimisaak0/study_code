#include "Point.h"

int main()
{
	Point p1, p2;

	p1.SetPosition(10, 20);	//p1의 좌표 설정
	p2.SetPosition(50, 60); //p2의 좌표 설정

	p1.Move(5, 0);
	p2.Move(0, 5);

	p1.Show();
	p2.Show();

	return 0;
}