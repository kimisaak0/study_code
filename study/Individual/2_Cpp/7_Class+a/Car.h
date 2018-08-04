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
	const int serial;		//const 멤버 변수

public:
	int temp;	//const 객체 실험용

	int getSerial() const { return serial; }
	void print() const;		//const 멤버 함수
	SerialCar(int Num, int s = 0, int g = 1, string c = "white");
};

class Temp
{
	int t;
public:
	Temp(int n) 
	{
		t = n;
		cout << "temp 생성자 호출 값은 " << t << endl; 
	}
};

class StaticClass
{
	static int n;
	// static int n2 = 100; //불가


public:

	//정수형 정적 상수 변수는 in-class initializer가 가능
	static const int R = 1000;
	//static const double d = 100.23; //불가

	static void showN();
	//static void showR() const;	//에러! 정적 멤버 함수에서 형식 한정자를 사용할 수 없습니다.

	StaticClass();
	~StaticClass();
};

class useclass
{
	Car useCar;

public:
	void useT() { useCar.print(); }
};