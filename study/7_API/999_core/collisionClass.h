#pragma once
#include "header.h"
#include <math.h>

struct sphere
{
	POINT pCenter;
	double dRadius;
};

class collisionClass
{
public:
	static bool RectInRect(RECT rtDesk, RECT rtSrc);
	static bool RectInPt(RECT rtDesk, POINT pt);
	static bool SphereInSphere(RECT rtDesk, RECT rtSrc);
	static bool SphereInPt(RECT rtDesk, POINT pt);

public:
	collisionClass();
	virtual ~collisionClass();
};

