#include "Car.h"



void Car::print() const
{
	cout << "�ӵ� : " << speed << " ��� : " << gear << " ���� : " << color << endl;
}
//
//void Car::print()
//{
//	cout << "�����ε�� print �Լ�" << endl;
//}

void Car::setSpeed(int speed)
{
	if (speed > 0) {
		this->speed = speed;		
	// this->speed�� ��� ����, speed�� �Ű� ����
	}
	else {
		this->speed = 0;
	}
}

void Car::isFaster(Car* p)
{
	if (this->getSpeed() > p->getSpeed()) {
	//���� ��ü�� ��� �Լ� > �Ű� ������ ��ü �Լ�
		cout << this->color;
		//���� ��ü�� ��� ����
	}
	else {
		cout << p->color;
		//�Ű� ������ ��� ����
	}

	cout << " color �ڵ����� �� ����" << endl;
}

Car::Car(int s, int g, string c)
{
	cout << "������ ȣ��" << endl;
	speed = s;
	gear = g;
	color = c;
}

Car::~Car()
{
	cout << "�Ҹ��� ȣ��" << endl;
}

void SerialCar::print() const	
{
	cout << "�ø��� �ѹ�" << serial;
	Car::print(); //const �Լ� �������� const �Լ��� ȣ�� �����ϴ�.
	
	//speed = 10; //const �Լ� ������ ������ �� ���� �Ұ�

	//setSpeed(50); //const�� �ƴ� �Լ� ��� �Ұ�(������)

	//cout << getSpeed() << endl; // ���� �������� �ʴ� �Լ����� const �Լ��� �ƴϸ� ����� �� ����. 
	cout << getSerial() << endl;	//�׷��Ƿ� �������� ��쿡�� const �Լ��� ����� ���� �Ϲ����̴�.
	
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