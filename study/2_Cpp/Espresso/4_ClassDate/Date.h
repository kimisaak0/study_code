#pragma once

#include <iostream>
#include <string>

//클래스 만들기
class Date
{
//'private' 직접 접근 불가
private:
	//'멤버 변수'(=필드) 선언
	int year;
	int month;
	int day;

//'public' 직접 접근 가능
public:
	std::string memo = "실험";
	
public:
	//'멤버 함수'(=메소드) 선언
	void setDate(int year, int month, int day);
	void printDate();
	int getYear();
	int getMonth();
	int getDay();
	Date(int year, int month, int day);
	Date();
	~Date();
};

