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

SOCKET Init()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) {
		ERR_EXIT(_T("윈속 초기화 실패"));
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
	TCHAR buf[256] = { 0, };
	while (true) {
		//메시지 전송
		char sendBuf[256] = { 0, };
		ZeroMemory(sendBuf, sizeof(sendBuf));
		std::cout << "입력 : "; fgets(sendBuf, 256, stdin);

		if (sendBuf[0] == '\n') {
			printf("종료합니다.\n");
			break; 
		} //엔터만 치면 종료시키기.

		size_t iLen = strlen(sendBuf);
		if (sendBuf[iLen - 1] == '\n') {
			sendBuf[iLen - 1] = '\0';
		}

		int iSendByte = 0;
		iSendByte = send(sock, sendBuf, (int)iLen, 0);  //데이터 전송 함수
		if (iSendByte == SOCKET_ERROR) {
			printf("서버가 닫혔습니다 \n");
			break;
		}
		std::cout << iSendByte << "byte 전송. \n";
	}
	return 0;
}

int RecvData(SOCKET client, TCHAR* retstr, int len)
{
	int left = len;

	TCHAR* ptr = retstr;

	while (left > 0) {
		int iRecv = recv(client, (char*)ptr, len, 0);
		if (iRecv == SOCKET_ERROR) {
			ERR_EXIT(_T("리시브 소켓 에러"));
			return -1;
		}
		else if (iRecv == 0) {
			break;
		}
		left -= iRecv;
		ptr += iRecv;
	}

	return len - left;
}


void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
