#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NBlocking_c.h"

SOCKET Init()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) {
		ERR_EXIT(L"���� �ʱ�ȭ ����");
		return -1;
	}

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		ERR_EXIT(_T("���� ���� ����"));
		return -1;
	}

	return sock;
}

bool IPConnect(SOCKET sock)
{
	int iRet = 0;

	// ���� ���� ó��
	do {
		if (iRet == SOCKET_ERROR) {
			std::cout << "IP�� �߸� �Է��ϼ̰ų�, ������ �����ֽ��ϴ�.\n";
			//return false;
		}

		std::string ip;
		std::cout << "������ IP�� �Է��ϼ���. \n";
		std::cin >> ip;

		SOCKADDR_IN sa_in;
		ZeroMemory(&sa_in, sizeof(sa_in));
		sa_in.sin_family = AF_INET;
		sa_in.sin_addr.s_addr = inet_addr(ip.c_str());     //���ڿ��� ���ڷ� ��ȯ
		sa_in.sin_port = htons(10000);                     //��Ʋ����ȿ��� �򿣵������ ��ȯ

		iRet = connect(sock, (sockaddr*)&sa_in, sizeof(sa_in));    //�Է��� IP�� ���ӽõ�.
	} while (iRet == SOCKET_ERROR);

	return true;
}

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

