#include "ovelapped1_c.h"

int main()
{
	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "���� ���� ���� \n";
	}

	getc(stdin); //���� ����

	DWORD dwSTID = 0;
	HANDLE hT = CreateThread(0, 0, SendThread, (LPVOID)sock, 0, &dwSTID);

	while (true) {
		//�޽��� �ޱ�
		char recvBuf[256] = { 0, };
		int iRecvByte = 0;
		iRecvByte = recv(sock, recvBuf, 256, 0);        //������ ���� �Լ�
		recvBuf[iRecvByte] = '\n';
		std::cout << recvBuf << std::endl;
	}

	Release(sock);
}