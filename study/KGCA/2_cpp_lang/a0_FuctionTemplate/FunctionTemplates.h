#pragma once
#include <iostream>
#include <string>
#include <string.h>

//�⺻���� �Լ� ���ø�
template <typename T>
T add(T x, T y)
{
	T result = x + y;

	return result;
}
//�Լ� ���ø��� Ư��ȭ 
template <>
char* add(char* x, char* y)
{
	char* result = new char[255]{ 0, };
	strcat_s(result,100, x);
	strcat_s(result,100, y);

	return result;
}

//�Լ� ���ø��� Ư��ȭ�� ��
template <>
double add(double x, double y)
{
	std::cout << "Ư��ȭ�� �Լ�" << std::endl;
	double result = x + y;
	return result;
}

//add �Լ��� �����ε� �� ��
//�����ε� �� �Լ��� �켱�õȴ�. �� �Լ� ���ø��� Ư��ȭ�� �ƴ� �����ε����� ó���� �� �ִ�.
double add(double x, double y) 
{
	std::cout << "�����ε��� �Լ�" << std::endl;
	double result = x + y;
	return result;
}

//���۷����� ���ڷ� �޴� ���ø�
template <typename T>
void Swap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}