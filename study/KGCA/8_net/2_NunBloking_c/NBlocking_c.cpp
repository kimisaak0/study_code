#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NBlocking_c.h"



int main()
{
	int iRet;

	SOCKET sock = Init();


	if (IPConnect(sock)) {
		std::cout << "서버 접속 성공 \n";
	}

	//논블록킹 소켓으로 전환
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) { return -1; }

	char buf[MAX_BUFFER_SIZE] = { 0, };
	int iEnd = 0;

	getc(stdin); //버퍼 비우기

	//메시지 처리
	while (true) {
		if ((bool)_kbhit() == true) {
			iRet = NonBlockingSocket(sock, FALSE);
			if (iRet == SOCKET_ERROR) { return -1; }

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

	Release(sock);

	return 0;
}

