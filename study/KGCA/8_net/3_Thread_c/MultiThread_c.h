#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include <conio.h>

static void ERR_EXIT(const TCHAR* msg)
{
	setlocale(LC_ALL, "KOREAN"); // 지역 설정.

	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(TCHAR*)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (TCHAR*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

static int NonBlockingSocket(SOCKET sock, u_long uMode)
{
	//To make NonBlocking Socket, controls the I/O mode of a socket
	int iRet = ioctlsocket(sock, FIONBIO, &uMode);
	if (iRet != NO_ERROR) {
		ERR_EXIT(_T("ioctlsocket"));
	}
	return iRet;
}

#define ACCEPTCHECK 0000
#define CHAT_MSG    1000

struct packHead
{
	WORD type;
	WORD length;
};

struct packet
{
	packHead ph;
	char buf[256];
};

int SendData(SOCKET sock, packet* pack)
{
	int iSendTotal = 0;
	do {
		int iSend = send(sock, (char*)pack, sizeof(packet) - iSendTotal, 0);
		iSendTotal += iSend;
	} while (iSendTotal < sizeof(packet));

	return iSendTotal;
}

int RecvData(SOCKET client, char* retstr)
{
	char buf[256] = { 0, };
	
	int iRecvTotal = 0;
	do {
		int iRecv = recv(client, &buf[iRecvTotal], sizeof(packHead) - iRecvTotal, 0);
		iRecvTotal += iRecv;
	} while (iRecvTotal < sizeof(packHead));
	if (iRecvTotal == 0 || iRecvTotal == SOCKET_ERROR) {
		return iRecvTotal;
	}

	packHead* recvPH = (packHead*)buf;
	switch (recvPH->type) {
		case ACCEPTCHECK: {
			return -2;
		} break;
		case CHAT_MSG: {
			do {
				int iRecv = recv(client, &buf[iRecvTotal], recvPH->length - iRecvTotal, 0);
				iRecvTotal += iRecv;
			} while (iRecvTotal < sizeof(recvPH->length));
			memcpy(retstr, buf, recvPH->length);
			return iRecvTotal;
		} break;
	}
}

SOCKET Init()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) {
		ERR_EXIT(L"윈속 초기화 실패");
		return -1;
	}

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		ERR_EXIT(_T("소켓 생성 실패"));
		return -1;
	}

	return sock;
}

bool IPConnect(SOCKET sock)
{
	int iRet = 0;

	// 서버 접속 처리
	do {
		if (iRet == SOCKET_ERROR) {
			std::cout << "IP를 잘못 입력하셨거나, 서버가 닫혀있습니다.\n";
			//return false;
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

	return true;
}

DWORD WINAPI SendThread(LPVOID arg) 
{
	SOCKET sock = (SOCKET)arg;
	char buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		fgets(buf, 256, stdin);
		if (buf[strlen(buf) - 1] == '\n') {
			buf[strlen(buf) - 1] = 0;
		}
		if (strlen(buf) == 0) { 
			printf("종료합니다.\n");
			break;
		} // 엔터는 종료!
		
		packHead ph = { CHAT_MSG, strlen(buf) };
		packet pack;
		pack.ph = ph;
		strcpy_s(pack.buf, buf);

		int iSendByte = SendData(sock, &pack);
		if (iSendByte == SOCKET_ERROR) { 
			printf("서버가 닫혔습니다 \n");
			break;
		}
		printf("전송 [%d] \n", iSendByte);
	}
	return 0;
}

void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
