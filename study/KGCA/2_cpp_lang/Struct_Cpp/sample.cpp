#include "Tpoint.h"



int main()
{
	{
		Tpoint p1, p2;
		p1.SetPosition(10, 20);
		p2.SetPosition(20, 30);
		p1.Move(5, 3);
		p2.Move(7, 6);
		p1.Show();
		p2.Show();
	}

	std::cout << "¾È³ç" << std::endl;
}