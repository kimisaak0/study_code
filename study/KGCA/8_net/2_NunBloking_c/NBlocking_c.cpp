#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NBlocking_c.h"

int main()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if ( iRet != (int)NO_ERROR) { 
		ERR_EXIT(L"윈속 초기화 실패");
		return -1; 
	}

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) {
		ERR_EXIT(_T("소켓 생성 실패"));
		return -1;
	}

	// 서버 접속 처리
	do {
		if (iRet == SOCKET_ERROR) {
			std::cout << "IP를 잘못 입력하셨거나, 서버가 닫혀있습니다.\n";
		}

		std::string ip;
		std::cout << "접속할 IP를 입력하세요. \n";
		std::cin >> ip;

		SOCKADDR_IN sa_in;
		ZeroMemory(&sa_in, sizeof(sa_in));
		sa_in.sin_family = AF_INET;
		sa_in.sin_addr.s_addr = inet_addr(ip.c_str());     //문자열을 숫자로 변환
		sa_in.sin_port = htons(10000);                     //리틀엔디안에서 빅엔디안으로 변환

		iRet = connect(sock, (sockaddr*)&sa_in, sizeof(sa_in));    //입력한 IP로 접속시도.
	} while (iRet == SOCKET_ERROR);

	std::cout << "서버 접속 성공 \n";

	//논블록킹 소켓으로 전환
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) { return -1; }

	char buf[MAX_BUFFER_SIZE] = { 0, };
	int iEnd = 0;

	//메시지 처리
	while (true) {
		if ((bool)_kbhit() == true) {
			iRet = NonBlockingSocket(sock, FALSE);
			if (iRet == SOCKET_ERROR) { return -1; }

			getc(stdin); //버퍼 비우기
			getc(stdin); //버퍼 비우기

			char sendBuf[256] = { 0, };
			ZeroMemory(sendBuf, sizeof(sendBuf));
			std::cout << "입력 : "; fgets(sendBuf, 256, stdin);
			if (sendBuf[0] == '\n') { break; } //엔터만 치면 종료시키기.

			size_t iLen = 0;
			iLen = strlen(sendBuf) - 1;

			int iSendByte = 0;
			iSendByte = send(sock, sendBuf, (int)iLen, 0);  //데이터 전송 함수
			std::cout << iSendByte << "byte 전송. \n";

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
					ERR_EXIT(_T("메시지 수신 실패"));
				}
				else {
					continue;
				}
			}
			//RecvBuf[iRecvByte] = 0;
			printf("받은 데이터 = %s\n", RecvBuf);
			ZeroMemory(RecvBuf, sizeof(RecvBuf));
		}
	}

	//8)
	closesocket(sock);
	WSACleanup();

	return 0;
}

