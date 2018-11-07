#include "Queue_arrayt.h"
#include "Stack_array.h"

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
	TCHAR strBuf[256];

	std::cout << "회문인지 확인할 문장을 입력하세요." << std::endl;
	tcin >> strBuf;

	int strLen = _tcslen(strBuf);

	QueueArray<TCHAR> unreverse(strLen);
	StackArray<TCHAR> reverse(strLen);

	for (int i = 0; i < strLen; i++) {
		unreverse.Add(strBuf[i]);
		reverse.Push(strBuf[i]);
	}

	bool Palindromes;

	while (true) {
		if (unreverse.Peek() != reverse.Peek()) {
			Palindromes = false;
			break;
		}

		unreverse.Remove();
		reverse.Pop();

		if (reverse.Count() == 0) {
			Palindromes = true;
			break;
		}
	} 

	tcout << strBuf << std::endl;

	if (Palindromes) {
		tcout << "위 문자열은 회문입니다." << std::endl;
	}
	else {
		tcout << "위 문자열은 회문이 아닙니다." << std::endl;
	}

}