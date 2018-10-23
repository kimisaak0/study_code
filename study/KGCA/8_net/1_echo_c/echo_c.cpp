#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	int ret = 0;

	WSADATA WSD;
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);        //윈도우 소켓 초기화
	if (ret != 0) { return -1; }

	
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);        //소켓 생성	
	if (sock == INVALID_SOCKET) { return -1; }

	

	do {
		if (ret == SOCKET_ERROR) {
			std::cout << "IP를 잘못 입력하셨거나, 서버가 닫혀있습니다.\n";
		}

		std::string ip;
		std::cout << "접속할 IP를 입력하세요. \n";
		std::cin >> ip;

		SOCKADDR_IN addrIn; 
		ZeroMemory(&addrIn, sizeof(addrIn));                        //htons : host to network short, ntohs : netword to host short     
		addrIn.sin_family = AF_INET;						        //host : Little Endian 사용(뒤집어져서 저장됨), network : Big Endian 사용 
		addrIn.sin_addr.s_addr = inet_addr(ip.c_str());		        //서버는 IP주소를 지정할 필요 없이 모든 IP(INADDR_ANY)를 받으면 된다.					
		addrIn.sin_port = htons(10000);                             //샘플용 프로그램의 포트번호는 10000으로 고정.   
	
		ret = connect(sock, (sockaddr*)&addrIn, sizeof(addrIn));    //입력한 IP로 접속시도.
	} while (ret == SOCKET_ERROR);

	


	

	getc(stdin);

	std::cout << "서버 접속 성공 \n";

	while (true) {
		//메시지 전송
		char sendBuf[256] = { 0, };
		std::cout << "입력 : "; fgets(sendBuf, 256, stdin);
		if (sendBuf[0] == '\n') { break; } //엔터만 치면 종료시키기.

		size_t iLen = 0;
		iLen = strlen(sendBuf) - 1;

		int iSendByte = 0;
		iSendByte = send(sock, sendBuf, (int)iLen, 0);  //데이터 전송 함수
		std::cout << iSendByte << "byte 전송. \n";

		//메시지 받기
		char recvBuf[256] = { 0, };
		int iRecvByte = 0;
		iRecvByte = recv(sock, recvBuf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			std::cout << "서버 종료";
		}
		recvBuf[iRecvByte] = '\n';

		std::cout << recvBuf << std::endl;
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