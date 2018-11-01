#include "Car.h"



void Car::print() const
{
	cout << "속도 : " << speed << " 기어 : " << gear << " 색상 : " << color << endl;
}
//
//void Car::print()
//{
//	cout << "오버로드된 print 함수" << endl;
//}

void Car::setSpeed(int speed)
{
	if (speed > 0) {
		this->speed = speed;		
	// this->speed는 멤버 변수, speed는 매개 변수
	}
	else {
		this->speed = 0;
	}
}

void Car::isFaster(Car* p)
{
	if (this->getSpeed() > p->getSpeed()) {
	//현재 객체의 멤버 함수 > 매개 변수의 객체 함수
		cout << this->color;
		//현재 객체의 멤버 변수
	}
	else {
		cout << p->color;
		//매개 변수의 멤버 변수
	}

	cout << " color 자동차가 더 빠름" << endl;
}

Car::Car(int s, int g, string c)
{
	cout << "생성자 호출" << endl;
	speed = s;
	gear = g;
	color = c;
}

Car::~Car()
{
	cout << "소멸자 호출" << endl;
}

void SerialCar::print() const	
{
	cout << "시리얼 넘버" << serial;
	Car::print(); //const 함수 내에서는 const 함수만 호출 가능하다.
	
	//speed = 10; //const 함수 내에서 변수의 값 변경 불가

	//setSpeed(50); //const가 아닌 함수 사용 불가(설정자)

	//cout << getSpeed() << endl; // 값을 변경하지 않는 함수여도 const 함수가 아니면 사용할 수 없다. 
	cout << getSerial() << endl;	//그러므로 접근자의 경우에는 const 함수로 만드는 것이 일반적이다.
	
}

SerialCar::SerialCar(int Num, int s, int g, string c) : Car(s, g, c), serial(Num)
{}

int StaticClass::n = 1;

void StaticClass::showN()
{
	cout << n << endl;
}


StaticClass::StaticClass()
{
	n++;
}

StaticClass::~StaticClass()
{
	n--;
}