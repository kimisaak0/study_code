#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NBlocking_c.h"



int main()
{
	int iRet;

	SOCKET sock = Init();


	if (IPConnect(sock)) {
		std::cout << "���� ���� ���� \n";
	}

	//����ŷ �������� ��ȯ
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) { return -1; }

	char buf[MAX_BUFFER_SIZE] = { 0, };
	int iEnd = 0;

	getc(stdin); //���� ����

	//�޽��� ó��
	while (true) {
		if ((bool)_kbhit() == true) {
			iRet = NonBlockingSocket(sock, FALSE);
			if (iRet == SOCKET_ERROR) { return -1; }

			getc(stdin); //���� ����

			char sendBuf[256] = { 0, };
			ZeroMemory(sendBuf, sizeof(sendBuf));
			std::cout << "�Է� : "; fgets(sendBuf, 256, stdin);
			if (sendBuf[0] == '\n') { break; } //���͸� ġ�� �����Ű��.

			size_t iLen = 0;
			iLen = strlen(sendBuf) - 1;

			int iSendByte = 0;
			iSendByte = send(sock, sendBuf, (int)iLen, 0);  //������ ���� �Լ�
			std::cout << iSendByte << "byte ����. \n";

			iRet = NonBlockingSocket(sock, TRUE);
			if (iRet == SOCKET_ERROR) { return -1; }
		}
		else {
			char RecvBuf[MAX_BUFFER_SIZE] = { 0, };
			// 7)
			int iRecvByte = recv(sock, RecvBuf, MAX_BUFFER_SIZE - 1, 0);
			if (iRecvByte == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					closesocket(sock);
					ERR_EXIT(_T("�޽��� ���� ����"));
				}
				else {
					continue;
				}
			}
			//RecvBuf[iRecvByte] = 0;
			printf("���� ������ = %s\n", RecvBuf);
			ZeroMemory(RecvBuf, sizeof(RecvBuf));
		}
	}

	Release(sock);

	return 0;
}

