#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	char* ip;

	std::cout << "접속할 IP를 입력하세요. \n";
	std::cin >> ip;	

	int ret;

	WSADATA WSD;
	
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);
	if (ret != 0) { return -1; }

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) { return -1; }

	SOCKADDR_IN addrIn;
	ZeroMemory(&addrIn, sizeof(addrIn));
	addrIn.sin_family = AF_INET;
	addrIn.sin_addr.s_addr = inet_addr(ip);
	addrIn.sin_port = htons(10000);

	ret = connect(sock, (sockaddr*)&addrIn, sizeof(addrIn));
	if (ret == SOCKET_ERROR) { return -1; }

	char buf[256] = { 0, };
	int iLen = 0;
	int iSendByte = 0;
	int iRecvByte = 0;

	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		std::cout << "입력 : ";
		fgets(buf, 256, stdin);
		if (buf[0] == '\n') { break; } //엔터만 치면 종료시키기.
		iLen = strlen(buf) - 1;
		iSendByte = send(sock, buf, iLen, 0);
		std::cout << iSendByte << "byte 전송. \n";

		ZeroMemory(buf, sizeof(char) * 256);
		iRecvByte = recv(sock, buf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			std::cout << "서버 종료";
		}
		buf[iRecvByte] = '\n';

		std::cout << buf << std::endl;
	}

	closesocket(sock);

	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "클린업 실패";
		return -1;
	}
	else {
		return -1;
	}

}