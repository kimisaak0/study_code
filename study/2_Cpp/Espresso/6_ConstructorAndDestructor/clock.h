#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class aliasName
{
	string& alias;

public:
	string getName();
	aliasName(string name);
	~aliasName();
};



class clock
{
private:
	//static int ClockCount = 0; //in-class initilizer�� �ִ� ����� const���� �մϴ�.
	static int ClockCount;

	//C++11�������� in-class initilizer�� ����������. (standard������ �� ��)
	// const int MAX_HOUR = 24;	//12 or 24	//C++11
	const int MAX_HOUR;						//standard
	
	int hour;
	int min;
	int sec;

	aliasName clockName;

public:
	void setClock(int h, int m, int s);
	void showClock();

	clock(string name, int MAX);
	clock(string name);
	clock(const clock& obj);
	~clock();
};

