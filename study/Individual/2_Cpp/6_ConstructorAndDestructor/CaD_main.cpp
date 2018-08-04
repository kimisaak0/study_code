#include "clock.h"

int main()
{
	clock a("first");
	clock b("second", 12);
	clock c = clock("third", 12);

	clock d = c;
}