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

	char buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		int iRecvByte = RecvData(sock, buf);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			printf("������ �������ϴ�.\n");
			break;
		}
		else if (iRecvByte > 0) {
			printf("���� �޽��� : %s", buf);
		}
	}

	CloseHandle(hT);


	Release(sock);
}