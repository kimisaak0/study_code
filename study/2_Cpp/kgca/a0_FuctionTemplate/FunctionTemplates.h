#pragma once
#include <iostream>
#include <string>
#include <string.h>

//기본적인 함수 템플릿
template <typename T>
T add(T x, T y)
{
	T result = x + y;

	return result;
}
//함수 템플릿의 특수화 
template <>
char* add(char* x, char* y)
{
	char* result = new char[255]{ 0, };
	strcat_s(result,100, x);
	strcat_s(result,100, y);

	return result;
}

//함수 템플릿을 특수화한 것
template <>
double add(double x, double y)
{
	std::cout << "특수화한 함수" << std::endl;
	double result = x + y;
	return result;
}

//add 함수를 오버로딩 한 것
//오버로딩 한 함수가 우선시된다. 즉 함수 템플릿은 특수화가 아닌 오버로딩으로 처리할 수 있다.
double add(double x, double y) 
{
	std::cout << "오버로딩한 함수" << std::endl;
	double result = x + y;
	return result;
}

//레퍼런스를 인자로 받는 템플릿
template <typename T>
void Swap(T& x, T& y)
{
	T temp = x;
	x = y;
	y = temp;
}