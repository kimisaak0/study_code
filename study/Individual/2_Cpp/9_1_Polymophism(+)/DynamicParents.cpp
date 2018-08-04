#include "DynamicParents.h"

void DynamicParents::printString()
{
	cout << s << endl;
}


DynamicParents::DynamicParents(const char* p)
{
	cout << "   Parents 持失切" << endl;
	s = new char[strlen(p) + 1];
	strcpy_s(s, strlen(p) + 1, p);
}


DynamicParents::~DynamicParents()
{
	cout << "   Parents 社瑚切" << endl;
	delete[] s;
}


void DynamicParents_noVirtual::printString()
{
	cout << "   " << s << endl;
}


DynamicParents_noVirtual::DynamicParents_noVirtual(const char* p)
{
	cout << "   Parents 持失切" << endl;
	s = new char[strlen(p) + 1];
	strcpy_s(s, strlen(p) + 1, p);
}


DynamicParents_noVirtual::~DynamicParents_noVirtual()
{
	cout << "   Parents 社瑚切" << endl;
	delete[] s;
}
