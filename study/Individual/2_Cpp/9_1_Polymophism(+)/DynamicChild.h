#pragma once
#include "DynamicParents.h"
class DynamicChild : public DynamicParents
{
private:
	char* tag;
	
public:
	void printString();

public:
	DynamicChild(const char* t, const char* p);
	virtual ~DynamicChild();
};

class DynamicChild_noVirtual : public DynamicParents_noVirtual
{
private:
	char* tag;

public:
	void printString();

public:
	DynamicChild_noVirtual(const char* t, const char* p);
	virtual ~DynamicChild_noVirtual();
};