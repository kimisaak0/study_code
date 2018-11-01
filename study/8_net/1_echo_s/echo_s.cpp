#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//소켓 생성
//연결형   : TCP(SOCK_STREAM, IPPROTO_TCP)
//비연결형 : UDP(SOCK_DGRAM,  IPPROTO_UDP) 


int main()
{
	int ret;

	WSADATA WSD;
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);        //윈도우 소켓 초기화
	if (ret != 0) { return -1; }
	
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);        //소켓 생성	
	if (sock == INVALID_SOCKET) { return -1; }

	//통신 정보 설정
	SOCKADDR_IN addrIn;
	ZeroMemory(&addrIn, sizeof(addrIn));           //htons : host to network short, ntohs : netword to host short    
	addrIn.sin_family = AF_INET;                   //host : Little Endian 사용(뒤집어져서 저장됨), network : Big Endian 사용 
	addrIn.sin_addr.s_addr = htonl(INADDR_ANY);    //서버는 IP주소를 지정할 필요 없이 모든 IP(INADDR_ANY)를 받으면 된다.
	addrIn.sin_port = htons(10000);                //샘플용 프로그램의 포트번호는 10000으로 고정.  
												   	
	ret = bind(sock, (SOCKADDR*)&addrIn, sizeof(addrIn));    // 소켓에 통신 정보 바인딩
	if (ret == SOCKET_ERROR) { return -1; }					 

	ret = listen(sock, SOMAXCONN);                           // 소켓을 대기 상태로 설정.
	if (ret == SOCKET_ERROR) { return -1; }
	
	while (true) {
		SOCKADDR_IN clientAddr;
		int addrlen = sizeof(clientAddr);

		SOCKET client = 0;
		client = accept(sock, (SOCKADDR*)&clientAddr, &addrlen);  //클라이언트 정보를 새로운 소켓을 만들어서 저장. (연결처리)
		if (client == INVALID_SOCKET) {
			printf("클라이언트 연결 실패");
			continue; 
		}
		printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(clientAddr.sin_addr));


		//에코 시스템
		while (true) {
			char recvBuf[256] = { 0, };
			ZeroMemory(recvBuf, sizeof(recvBuf));
			int iRecvByte = 0;
			iRecvByte = recv(client, recvBuf, 256, 0);   //데이터를 받는다. 에러면 SOCKET_ERROR, 정상이면 받은 데이터크기를 반환한다.
			if (iRecvByte == 0)  {
				printf("클라이언트 정상 종료 [ip:%s]", inet_ntoa(clientAddr.sin_addr));
				break;
			}
			else if (iRecvByte == SOCKET_ERROR) {
				printf("클라이언트 비정상 종료 [ip:%s]", inet_ntoa(clientAddr.sin_addr));
				break;
			}
			recvBuf[iRecvByte] = '\n';
			printf("%s", recvBuf);

			int iSendByte = 0;
			iSendByte = send(client, recvBuf, iRecvByte, 0);  //데이터를 보낸다. 
			if (iSendByte == SOCKET_ERROR) {
				printf("send 실패");
				continue;
			}
		}
		//클라이언트 종료
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