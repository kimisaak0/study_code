#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Car
{
protected:
	int speed;
	int gear;
	string color;

public:
	int pub;

	void print() const;
//	void print();


	int getSpeed() { return speed; }
	void setSpeed(int speed);
	void isFaster(Car* p);

	Car(int s = 0, int g = 1, string c = "white");
	~Car();
};

class SerialCar : public Car
{
	const int serial;		//const ��� ����

public:
	int temp;	//const ��ü �����

	int getSerial() const { return serial; }
	void print() const;		//const ��� �Լ�
	SerialCar(int Num, int s = 0, int g = 1, string c = "white");
};

class Temp
{
	int t;
public:
	Temp(int n) 
	{
		t = n;
		cout << "temp ������ ȣ�� ���� " << t << endl; 
	}
};

class StaticClass
{
	static int n;
	// static int n2 = 100; //�Ұ�


public:

	//������ ���� ��� ������ in-class initializer�� ����
	static const int R = 1000;
	//static const double d = 100.23; //�Ұ�

	static void showN();
	//static void showR() const;	//����! ���� ��� �Լ����� ���� �����ڸ� ����� �� �����ϴ�.

	StaticClass();
	~StaticClass();
};

class useclass
{
	Car useCar;

public:
	void useT() { useCar.print(); }
};