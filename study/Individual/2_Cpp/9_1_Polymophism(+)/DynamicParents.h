#pragma once
#include "Header.h"

class DynamicParents
{
protected:
	char* s;

public:
	virtual void printString();

public:
	DynamicParents(const char* p);
	virtual ~DynamicParents();
};

class DynamicParents_noVirtual
{
protected:
	char* s;

public:
	virtual void printString();

public:
	DynamicParents_noVirtual(const char* p);
	~DynamicParents_noVirtual();
};