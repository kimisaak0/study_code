#include "collisionClass.h"



collisionClass::collisionClass()
{
}

bool collisionClass::RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT cDesk, cSrc;
	cDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cSrc.y = (rtSrc.top + rtSrc.bottom) / 2;

	POINT radius;
	radius.x = abs(cDesk.x - cSrc.x);
	radius.y = abs(cDesk.y - cSrc.y);

	POINT deskRadius, srcRadius;
	deskRadius.x = (rtDesk.right - rtDesk.left) / 2;
	deskRadius.y = (rtDesk.bottom - rtDesk.top) / 2;
	srcRadius.x = (rtSrc.right - rtSrc.left) / 2;
	srcRadius.y = (rtSrc.bottom - rtSrc.top) / 2;

	if (radius.x <= (deskRadius.x + srcRadius.x) &&
		radius.y <= (deskRadius.y + srcRadius.y)) {
		return true;
	}

	return false;
}

bool collisionClass::RectInPt(RECT rt, POINT pt)
{
	if ((rt.left <= pt.x && rt.right >= pt.x) &&
		(rt.top <= pt.y && rt.bottom >= pt.y)) {
		return true;
	}
	return false;
}

bool collisionClass::SphereInSphere(RECT rtDesk, RECT rtSrc)
{
	sphere sphereDesk, sphereSrc;

	sphereDesk.pCenter.x = (rtDesk.left + rtDesk.right) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + rtDesk.bottom) / 2;
	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	sphereDesk.dRadius = (dwX < dwY) ? dwY : dwX;

	sphereSrc.pCenter.x = (rtSrc.left + rtSrc.right) / 2;
	sphereSrc.pCenter.y = (rtSrc.top + rtSrc.bottom) / 2;
	dwX = (rtSrc.right - rtSrc.left) / 2;
	dwY = (rtSrc.bottom - rtSrc.top) / 2;
	sphereSrc.dRadius = (dwX < dwY) ? dwY : dwX;

	double dDistance =
		sqrt(pow((sphereDesk.pCenter.x - sphereSrc.pCenter.x), 2) +
			pow((sphereDesk.pCenter.y - sphereSrc.pCenter.y), 2));

	if (dDistance < (sphereDesk.dRadius + sphereSrc.dRadius)) {
		return true;
	}

	return false;
}

bool collisionClass::SphereInPt(RECT rtDesk, POINT pt)
{
	sphere sphereDesk;
	sphereDesk.pCenter.x = (rtDesk.left + rtDesk.right) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + rtDesk.bottom) / 2;
	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	sphereDesk.dRadius = (dwX < dwY) ? dwY : dwX;

	double dDistance =
		sqrt(pow((sphereDesk.pCenter.x - pt.x), 2) +
			pow((sphereDesk.pCenter.y - pt.y), 2));

	if (dDistance < sphereDesk.dRadius) {
		return true;
	}

	return false;

}

collisionClass::~collisionClass()
{
}
