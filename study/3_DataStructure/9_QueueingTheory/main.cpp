
#include "header.h"

int main()
{
	simulator queueing;

	int enter;

	do {
		queueing.Display();
		std::cin >> enter;
		queueing.Work(enter);
	} while (enter < 999);
}