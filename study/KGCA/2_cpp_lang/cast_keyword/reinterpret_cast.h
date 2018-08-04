#pragma once
#include "header.h"

namespace rei
{
	//reinterpret_cast 강제 형변환에 사용.
	//보통 포인터->데이터, 포인터->포인터 형변환에 사용된다.

	unsigned short hash_1(void* p)
	{
		//주소를 정수로 변환.
		unsigned int val = reinterpret_cast<unsigned int>(p);
		return (unsigned short) (val ^ (val >> 16));
	}

	int g_iArray[10][10];

	unsigned short hash_2(void* p)
	{
		unsigned short val = reinterpret_cast<unsigned short>(p);
		return val % 10;
	}

	void set(int iRow, int iValue)
	{
		for (int iCnt = 0; iCnt < 10; iCnt++) {
			if (g_iArray[iRow][iCnt] <= 0) {
				g_iArray[iRow][iCnt] = iValue;
				break;
			}
		}
	}

	int get(int iRow, int iValue)
	{
		for (int iCnt = 0; iCnt < 10; iCnt++) {
			if (g_iArray[iRow][iCnt] == iValue) {
				return g_iArray[iRow][iCnt];	
			}
		}
		return -1;
	}

}