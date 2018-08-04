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
	cout << ClockCount << "��° �ð� : " << clockName.getName() << endl;
	cout << hour << "�� " << min << "�� " << sec << "�� " << endl;
}

clock::clock(string name, int MAX) : clockName(name), MAX_HOUR(MAX)
{
	cout << ClockCount << "��� �ʱ�ȭ ����� ����ϴ� ������ ȣ��. (��� ������ ����� ��ü)" << endl;
	ClockCount++;
	hour = 0;
	min = 0;
	sec = 0;
}

clock::clock(string name) : clockName(name), MAX_HOUR(24)
{
	cout << ClockCount << "��� �ʱ�ȭ ����� ����ϴ� ������ ȣ��. (��� ������ ��ü)" << endl;
	ClockCount++;
	hour = 0;
	min = 0;
	sec = 0;
}

clock::clock(const clock& obj) : clockName(obj.clockName), MAX_HOUR(obj.MAX_HOUR)
{
	cout << ClockCount << "���� ������ ȣ��" << endl;
	ClockCount++;
	hour = obj.hour;
	min = obj.min;
	sec = obj.sec;
}

clock::~clock()
{
	cout << ClockCount << "����Ʈ �Ҹ��� ȣ��" << endl;
	ClockCount--;
}

string aliasName::getName()
{
	return alias;
}

aliasName::aliasName(string name) : alias(name)
{
	cout << "��ü ���� ��ü ����" << endl;
}

aliasName::~aliasName()
{

}

