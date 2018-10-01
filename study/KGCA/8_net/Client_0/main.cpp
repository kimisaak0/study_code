#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32")


int main()
{
	WSADATA wd;
	//���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
		return 1;
	}

	//���� ���� (TCP�� ������)
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) { 
		return 1; 
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = inet_addr("192.168.0.101");  //127.�� �������ּ�
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //127.�� �������ּ�
	addr.sin_port = htons(10000);

	//Ŭ���̾�Ʈ���� ������ ����
	int ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	char buffer[256] = { 0, };


	char buffer2[256] = " ���̻� ready";

	//strcat_s(buffer, buffer2);
	
	while (true) {
		recv(sock, buffer, sizeof(buffer), 0);
		std::cout << buffer;
		std::cin >> buffer2;
		send(sock, buffer2, sizeof(buffer2), 0);
	}

	//���� ����
	closesocket(sock);

	WSACleanup();

	std::cout << "HELLO";
}