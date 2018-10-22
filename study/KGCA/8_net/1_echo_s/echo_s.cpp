#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//소켓 생성
//연결형   : TCP(SOCK_STREAM, IPPROTO_TCP)
//비연결형 : UDP(SOCK_DGRAM,  IPPROTO_UDP) 

int main()
{
	//클라와 서버가 다른 부분 1 
	// 서버는 IP주소를 지정할 필요 없이 모든 IP를 받으면 된다. (차단할 거 아니면)

	WSADATA WSD;
	int ret;

	//윈도우 소켓 초기화
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
	//샘플용 프로그램의 포트번호는 10000으로 고정.
	addrIn.sin_port = htons(10000);
	//htons : host to network short, ntohs : netword to host short
	//host : Little Endian 사용(뒤집어져서 저장됨), network : Big Endian 사용

	//클라와 서버가 다른 부분 2
	//소켓을 대상 IP에 연결해라.
	ret = bind(sock, (SOCKADDR*)&addrIn, sizeof(addrIn));
	if (ret == SOCKET_ERROR) { return -1; }

	ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) { return -1; }


	//클라와 서버가 다른 부분 3
	SOCKADDR_IN clientAddr;
	SOCKET client;
	
	while (true) {
		//클라이언트 접속 받기
		int addrlen = sizeof(clientAddr);
		client = accept(sock, (SOCKADDR*)&clientAddr, &addrlen);
		printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(clientAddr.sin_addr));

		char buf[256] = { 0, };
		int iLen = 0;
		int iSendByte = 0;
		int iRecvByte = 0;

		while (true) {
			iRecvByte = recv(client, buf, 256, 0);
			if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
				printf("클라이언트 접속 종료 [ip:%s]", inet_ntoa(clientAddr.sin_addr));
				break; //클라이언트 종료
			}
			buf[iRecvByte] = '\n';
			printf("%s", buf);
			iSendByte = send(client, buf, iRecvByte, 0);
		}
		//
		closesocket(client);
	}

	closesocket(sock);
	//윈도우 소켓 소멸
	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "클린업 실패";
		return -1;
	}
	else {
		return ret;
	}

}