#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "MultiThread_c.h"

int main()
{
	int iRet;

	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "���� ���� ���� \n";
	}



	Release(sock);
}