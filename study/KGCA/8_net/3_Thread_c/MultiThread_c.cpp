#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "MultiThread_c.h"

int main()
{
	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "���� ���� ���� \n";
	}

	getc(stdin); //���� ����

	DWORD dwSTID = 0;
	HANDLE hT = CreateThread(0, 0, SendThread, (LPVOID)sock, 0, &dwSTID);

	TCHAR buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		int iRecvByte = RecvData(sock, buf);
		if (iRecvByte == SOCKET_ERROR) {
			printf("������ �������ϴ�.\n");
			break;
		}
		else if (iRecvByte > 0) {
			_tprintf(_T("echo : %s\n"), buf);
		}
	}

	CloseHandle(hT);


	Release(sock);
}