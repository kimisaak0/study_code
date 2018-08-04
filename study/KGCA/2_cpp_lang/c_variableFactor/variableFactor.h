#pragma once

#include <iostream> //initializer_list, vfprintf
#include <initializer_list> //initializer_list
#include <cstdarg> //va_list
using std::cout;
using std::endl;
using std::initializer_list;

bool g_debug = false;

#pragma region C_style
void debugOut(const char* str, ...)
{
	va_list ap;
	if (g_debug)
	{
		va_start(ap, str);
		//vfprintf of vprintf를 사용해야한다
	    //printf 함수를 사용하면 안됨.
		vfprintf(stderr, str, ap);
		va_end(ap);
	}
}

void printInts(int num, ...)
{
	int temp;
	va_list ap;
	va_start(ap, num);
	for (int iCnt = 0; iCnt < num; iCnt++) {
		temp = va_arg(ap, int);
		cout << temp << " ";
	}
	va_end(ap);
	cout << endl;
}
#pragma endregion

#pragma region C++11_style
//int만 초기화된다.
int makeSum(initializer_list<int> Ist)
{
	int total = 0;
	for (auto iter = Ist.begin(); iter != Ist.end(); ++iter) {
		total += (*iter);
	}
	return total;
}
#pragma endregion

