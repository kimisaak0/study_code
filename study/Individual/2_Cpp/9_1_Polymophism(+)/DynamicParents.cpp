#include "DynamicParents.h"

void DynamicParents::printString()
{
	cout << s << endl;
}


DynamicParents::DynamicParents(const char* p)
{
	cout << "   Parents ������" << endl;
	s = new char[strlen(p) + 1];
	strcpy_s(s, strlen(p) + 1, p);
}


DynamicParents::~DynamicParents()
{
	cout << "   Parents �Ҹ���" << endl;
	delete[] s;
}


void DynamicParents_noVirtual::printString()
{
	cout << "   " << s << endl;
}


DynamicParents_noVirtual::DynamicParents_noVirtual(const char* p)
{
	cout << "   Parents ������" << endl;
	s = new char[strlen(p) + 1];
	strcpy_s(s, strlen(p) + 1, p);
}


DynamicParents_noVirtual::~DynamicParents_noVirtual()
{
	cout << "   Parents �Ҹ���" << endl;
	delete[] s;
}
