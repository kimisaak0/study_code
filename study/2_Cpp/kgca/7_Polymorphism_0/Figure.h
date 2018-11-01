#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Figure //�⺻ �θ� Ŭ����
{
protected:
     int x;       //�߽��� x��ǥ
     int y;       //�߽��� y��ǥ
     int width;   //���α���
     int height;  //���α���

public:     
	 void move(int x, int y);
	 void resize(int width, int height);
	 virtual void draw();	//�����Լ�
	 void shape();          //�����Լ��� �ƴ�

public:
	Figure();
	Figure(int x, int y, int width, int height);
	virtual ~Figure();
};

