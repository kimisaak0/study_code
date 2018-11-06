#include "stack_array.h"
#include <iostream>
#include <tchar.h>

#if defined(UNICODE) || defined(_UNICODE)
#define tcout std::wcout
#define tcin std::wcin

#else
#define tcout std::cout
#define tcin std::cin

#endif

int main()
{
	TCHAR str[256] = { 0, };
	tcout << "뒤집을 문자열을 입력하세요" << std::endl;
	tcin >> str;

	int strLen = _tcslen(str);
	StackArray<TCHAR> rStr(strLen);
	
	for (int i = 0; i < strLen; i++) {
		rStr.Push(str[i]);
	}

	for (int i = 0; i < strLen; i++) {
		tcout << rStr.Peek();
		rStr.Pop();
	}
	tcout << std::endl;
}