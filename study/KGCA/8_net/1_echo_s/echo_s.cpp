#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//���� ����
//������   : TCP(SOCK_STREAM, IPPROTO_TCP)
//�񿬰��� : UDP(SOCK_DGRAM,  IPPROTO_UDP) 

int main()
{
	//Ŭ��� ������ �ٸ� �κ� 1 
	// ������ IP�ּҸ� ������ �ʿ� ���� ��� IP�� ������ �ȴ�. (������ �� �ƴϸ�)

	WSADATA WSD;
	int ret;

	//������ ���� �ʱ�ȭ
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);
	if (ret != 0) { return -1; }

	//
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) { return -1; }

	//
	SOCKADDR_IN addrIn;
	ZeroMemory(&addrIn, sizeof(addrIn));
	addrIn.sin_family = AF_INET;
	addrIn.sin_addr.s_addr = htonl(INADDR_ANY);
	//���ÿ� ���α׷��� ��Ʈ��ȣ�� 10000���� ����.
	addrIn.sin_port = htons(10000);
	//htons : host to network short, ntohs : netword to host short
	//host : Little Endian ���(���������� �����), network : Big Endian ���

	//Ŭ��� ������ �ٸ� �κ� 2
	//������ ��� IP�� �����ض�.
	ret = bind(sock, (SOCKADDR*)&addrIn, sizeof(addrIn));
	if (ret == SOCKET_ERROR) { return -1; }

	ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) { return -1; }


	//Ŭ��� ������ �ٸ� �κ� 3
	SOCKADDR_IN clientAddr;
	SOCKET client;
	
	while (true) {
		//Ŭ���̾�Ʈ ���� �ޱ�
		int addrlen = sizeof(clientAddr);
		client = accept(sock, (SOCKADDR*)&clientAddr, &addrlen);
		printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(clientAddr.sin_addr));

		char buf[256] = { 0, };
		int iLen = 0;
		int iSendByte = 0;
		int iRecvByte = 0;

		while (true) {
			iRecvByte = recv(client, buf, 256, 0);
			if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
				printf("Ŭ���̾�Ʈ ���� ���� [ip:%s]", inet_ntoa(clientAddr.sin_addr));
				break; //Ŭ���̾�Ʈ ����
			}
			buf[iRecvByte] = '\n';
			printf("%s", buf);
			iSendByte = send(client, buf, iRecvByte, 0);
		}
		//
		closesocket(client);
	}

	closesocket(sock);
	//������ ���� �Ҹ�
	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "Ŭ���� ����";
		return -1;
	}
	else {
		return ret;
	}

}