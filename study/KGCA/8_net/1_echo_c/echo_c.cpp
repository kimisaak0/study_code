#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA WSD;
	int ret = 0;

	//���� �ʱ�ȭ
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);
	if (ret != 0) { return -1; }

	//
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) { return -1; }

	std::string ip;

	do {
		if (ret == SOCKET_ERROR) {
			std::cout << "IP�� �߸� �Է��ϼ̰ų�, ������ �����ֽ��ϴ�.\n";
		}

		std::cout << "������ IP�� �Է��ϼ���. \n";
		std::cin >> ip;

		SOCKADDR_IN addrIn;
		ZeroMemory(&addrIn, sizeof(addrIn));
		addrIn.sin_family = AF_INET;
		addrIn.sin_addr.s_addr = inet_addr(ip.c_str());
		//���ÿ� ���α׷��� ��Ʈ��ȣ�� 10000���� ����.
		addrIn.sin_port = htons(10000);
		//htons : host to network short, ntohs : netword to host short
		//host : Little Endian ���(���������� �����), network : Big Endian ���

		ret = connect(sock, (sockaddr*)&addrIn, sizeof(addrIn));
	} while (ret == SOCKET_ERROR);

	char buf[256] = { 0, };
	size_t iLen = 0;
	int iSendByte = 0;
	int iRecvByte = 0;

	getc(stdin);

	std::cout << "���� ���� ���� \n";

	while (true) {
		//�޽��� ������
		ZeroMemory(buf, sizeof(char) * 256);
		std::cout << "�Է� : ";
		 fgets(buf, 256, stdin);
		if (buf[0] == '\n') { break; } //���͸� ġ�� �����Ű��.
		iLen = strlen(buf) - 1;
		iSendByte = send(sock, buf, (int)iLen, 0);
		std::cout << iSendByte << "byte ����. \n";

		//���� �ޱ�
		ZeroMemory(buf, sizeof(char) * 256);
		iRecvByte = recv(sock, buf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			std::cout << "���� ����";
		}
		buf[iRecvByte] = '\n';

		std::cout << buf << std::endl;
	}

	//
	closesocket(sock);

	//
	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "Ŭ���� ����";
		return -1;
	}
	else {
		return 0;
	}

}