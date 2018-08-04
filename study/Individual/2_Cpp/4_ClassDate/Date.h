#pragma once

#include <iostream>
#include <string>

//Ŭ���� �����
class Date
{
//'private' ���� ���� �Ұ�
private:
	//'��� ����'(=�ʵ�) ����
	int year;
	int month;
	int day;

//'public' ���� ���� ����
public:
	std::string memo = "����";
	
public:
	//'��� �Լ�'(=�޼ҵ�) ����
	void setDate(int year, int month, int day);
	void printDate();
	int getYear();
	int getMonth();
	int getDay();
	Date(int year, int month, int day);
	Date();
	~Date();
};

