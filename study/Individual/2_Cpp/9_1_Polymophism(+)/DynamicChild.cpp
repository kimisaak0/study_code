#include "DynamicChild.h"

void DynamicChild::printString()
{
	cout << "   " << tag << s << tag << endl;
}


DynamicChild::DynamicChild(const char* t, const char* p) : DynamicParents(p)
{
	cout << "   child 持失切" << endl;
	tag = new char[strlen(t) + 1];
	strcpy_s(tag,strlen(t)+1,t);
}


DynamicChild::~DynamicChild()
{
	cout << "   child 社瑚切" << endl;
	delete[] tag;
}

void DynamicChild_noVirtual::printString()
{
	cout << "   " << tag << s << tag << endl;
}


DynamicChild_noVirtual::DynamicChild_noVirtual(const char* t, const char* p) : DynamicParents_noVirtual(p)
{
	cout << "   child 持失切" << endl;
	tag = new char[strlen(t) + 1];
	strcpy_s(tag, strlen(t) + 1, t);
}


DynamicChild_noVirtual::~DynamicChild_noVirtual()
{
	cout << "   child 社瑚切" << endl;
	delete[] tag;
}

