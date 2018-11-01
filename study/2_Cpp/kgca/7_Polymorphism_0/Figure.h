#pragma once
#include <iostream>
using std::cout;
using std::endl;

class Figure //기본 부모 클래스
{
protected:
     int x;       //중심의 x좌표
     int y;       //중심의 y좌표
     int width;   //가로길이
     int height;  //세로길이

public:     
	 void move(int x, int y);
	 void resize(int width, int height);
	 virtual void draw();	//가상함수
	 void shape();          //가상함수가 아님

public:
	Figure();
	Figure(int x, int y, int width, int height);
	virtual ~Figure();
};

