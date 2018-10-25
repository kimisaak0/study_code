#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "MultiThread_c.h"

int main()
{
	int iRet;

	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "서버 접속 성공 \n";
	}



	Release(sock);
}