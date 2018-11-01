#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "MultiThread_c.h"

int main()
{
	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "서버 접속 성공 \n";
	}

	getc(stdin); //버퍼 비우기

	DWORD dwSTID = 0;
	HANDLE hT = CreateThread(0, 0, SendThread, (LPVOID)sock, 0, &dwSTID);

	TCHAR buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		int iRecvByte = RecvData(sock, buf);
		if (iRecvByte == SOCKET_ERROR) {
			printf("서버가 닫혔습니다.\n");
			break;
		}
		else if (iRecvByte > 0) {
			_tprintf(_T("echo : %s\n"), buf);
		}
	}

	CloseHandle(hT);


	Release(sock);
}