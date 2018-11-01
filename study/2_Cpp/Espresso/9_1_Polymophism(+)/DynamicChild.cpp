#include "DynamicChild.h"

void DynamicChild::printString()
{
	cout << "   " << tag << s << tag << endl;
}


DynamicChild::DynamicChild(const char* t, const char* p) : DynamicParents(p)
{
	cout << "   child ������" << endl;
	tag = new char[strlen(t) + 1];
	strcpy_s(tag,strlen(t)+1,t);
}


DynamicChild::~DynamicChild()
{
	cout << "   child �Ҹ���" << endl;
	delete[] tag;
}

void DynamicChild_noVirtual::printString()
{
	cout << "   " << tag << s << tag << endl;
}


DynamicChild_noVirtual::DynamicChild_noVirtual(const char* t, const char* p) : DynamicParents_noVirtual(p)
{
	cout << "   child ������" << endl;
	tag = new char[strlen(t) + 1];
	strcpy_s(tag, strlen(t) + 1, t);
}


DynamicChild_noVirtual::~DynamicChild_noVirtual()
{
	cout << "   child �Ҹ���" << endl;
	delete[] tag;
}

