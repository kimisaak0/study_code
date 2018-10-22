#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA WSD;
	int ret = 0;

	//윈속 초기화
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);
	if (ret != 0) { return -1; }

	//
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) { return -1; }

	std::string ip;

	do {
		if (ret == SOCKET_ERROR) {
			std::cout << "IP를 잘못 입력하셨거나, 서버가 닫혀있습니다.\n";
		}

		std::cout << "접속할 IP를 입력하세요. \n";
		std::cin >> ip;

		SOCKADDR_IN addrIn;
		ZeroMemory(&addrIn, sizeof(addrIn));
		addrIn.sin_family = AF_INET;
		addrIn.sin_addr.s_addr = inet_addr(ip.c_str());
		//샘플용 프로그램의 포트번호는 10000으로 고정.
		addrIn.sin_port = htons(10000);
		//htons : host to network short, ntohs : netword to host short
		//host : Little Endian 사용(뒤집어져서 저장됨), network : Big Endian 사용

		ret = connect(sock, (sockaddr*)&addrIn, sizeof(addrIn));
	} while (ret == SOCKET_ERROR);

	char buf[256] = { 0, };
	size_t iLen = 0;
	int iSendByte = 0;
	int iRecvByte = 0;

	getc(stdin);

	std::cout << "서버 접속 성공 \n";

	while (true) {
		//메시지 보내기
		ZeroMemory(buf, sizeof(char) * 256);
		std::cout << "입력 : ";
		 fgets(buf, 256, stdin);
		if (buf[0] == '\n') { break; } //엔터만 치면 종료시키기.
		iLen = strlen(buf) - 1;
		iSendByte = send(sock, buf, (int)iLen, 0);
		std::cout << iSendByte << "byte 전송. \n";

		//에코 받기
		ZeroMemory(buf, sizeof(char) * 256);
		iRecvByte = recv(sock, buf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			std::cout << "서버 종료";
		}
		buf[iRecvByte] = '\n';

		std::cout << buf << std::endl;
	}

	//
	closesocket(sock);

	//
	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "클린업 실패";
		return -1;
	}
	else {
		return 0;
	}

}