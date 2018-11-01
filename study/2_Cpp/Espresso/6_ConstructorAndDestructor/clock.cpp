#include "clock.h"

int clock::ClockCount = 0;

void clock::setClock(int h, int m, int s)
{
	hour = h /MAX_HOUR + m / 60;
	min = m % 60 + s / 60;
	sec = s % 60;
}

void clock::showClock() 
{
	cout << ClockCount << "번째 시계 : " << clockName.getName() << endl;
	cout << hour << "시 " << min << "분 " << sec << "초 " << endl;
}

clock::clock(string name, int MAX) : clockName(name), MAX_HOUR(MAX)
{
	cout << ClockCount << "멤버 초기화 목록을 사용하는 생성자 호출. (멤버 변수가 상수와 객체)" << endl;
	ClockCount++;
	hour = 0;
	min = 0;
	sec = 0;
}

clock::clock(string name) : clockName(name), MAX_HOUR(24)
{
	cout << ClockCount << "멤버 초기화 목록을 사용하는 생성자 호출. (멤버 변수가 객체)" << endl;
	ClockCount++;
	hour = 0;
	min = 0;
	sec = 0;
}

clock::clock(const clock& obj) : clockName(obj.clockName), MAX_HOUR(obj.MAX_HOUR)
{
	cout << ClockCount << "복사 생성자 호출" << endl;
	ClockCount++;
	hour = obj.hour;
	min = obj.min;
	sec = obj.sec;
}

clock::~clock()
{
	cout << ClockCount << "디폴트 소멸자 호출" << endl;
	ClockCount--;
}

string aliasName::getName()
{
	return alias;
}

aliasName::aliasName(string name) : alias(name)
{
	cout << "객체 속의 객체 생성" << endl;
}

aliasName::~aliasName()
{

}

