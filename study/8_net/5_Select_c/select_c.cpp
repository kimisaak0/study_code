#include "select_c.h"

int main()
{
	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "서버 접속 성공 \n";
	}

	getc(stdin); //버퍼 비우기

	while (true) {
		//메시지 전송
		char sendBuf[256] = { 0, };
		ZeroMemory(sendBuf, sizeof(sendBuf));
		std::cout << "입력 : "; fgets(sendBuf, 256, stdin);
		
		if (sendBuf[0] == '\n') { break; } //엔터만 치면 종료시키기.

		size_t iLen = strlen(sendBuf);
		if (sendBuf[iLen - 1] == '\n') {
			sendBuf[iLen - 1] = '\0';
		}
		
		int iSendByte = 0;
		iSendByte = send(sock, sendBuf, (int)iLen, 0);  //데이터 전송 함수
		std::cout << iSendByte << "byte 전송. \n";

		//메시지 받기
		char recvBuf[256] = { 0, };
		int iRecvByte = 0;
		iRecvByte = recv(sock, recvBuf, 256, 0);        //데이터 수신 함수
		recvBuf[iRecvByte] = '\n';
		std::cout << recvBuf << std::endl;
	}

	Release(sock);
}