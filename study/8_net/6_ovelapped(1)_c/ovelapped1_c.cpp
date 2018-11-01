#include "ovelapped1_c.h"

int main()
{
	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "서버 접속 성공 \n";
	}

	getc(stdin); //버퍼 비우기

	DWORD dwSTID = 0;
	HANDLE hT = CreateThread(0, 0, SendThread, (LPVOID)sock, 0, &dwSTID);

	while (true) {
		//메시지 받기
		char recvBuf[256] = { 0, };
		int iRecvByte = 0;
		iRecvByte = recv(sock, recvBuf, 256, 0);        //데이터 수신 함수
		recvBuf[iRecvByte] = '\n';
		std::cout << recvBuf << std::endl;
	}

	Release(sock);
}