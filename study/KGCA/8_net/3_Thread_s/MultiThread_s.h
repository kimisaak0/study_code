#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>
#include <list>

std::list<SOCKET> g_userlist;

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


SOCKET Init()
{
	int iRet;

	SOCKET sock;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) {
		ERR_EXIT(_T("윈속 초기화 실패"));
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);


	SOCKADDR_IN sa_in;
	ZeroMemory(&sa_in, sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_in.sin_port = htons(10000);

	// 0) 통신 환경 정보를 갖는 소켓을 생성. 이후 이 소켓을 이용해 실제 접속한 클라이언트 소켓을 생성함. (대기 소켓이라는 뜻)
	iRet = bind(sock, (sockaddr*)&sa_in, sizeof(sa_in));
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("소켓에 통신 환경 바인딩 실패"));
		return -1;
	}

	// 1)클라이언트가 접속할 때 까지 대기
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("대기상태 설정 실패"));
		return -1;
	}

	return sock;
}


bool ClientAccept(SOCKET sock)
{
	NonBlockingSocket(sock, TRUE);

	SOCKADDR_IN client_addr;
	int addrlen = sizeof(client_addr);

	SOCKET client = 0;
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //클라이언트 정보를 새로운 소켓을 만들어서 저장. (연결처리)
	if (client == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			ERR_EXIT(_T("클라이언트 연결 실패"));
		}
		return false;
	}
	else {
		printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
		g_userlist.push_back(client);
	}

	NonBlockingSocket(sock, FALSE);

	return true;
}

void acceptCheck()
{
	std::list<SOCKET>::iterator iter;
	for (iter = g_userlist.begin(); iter != g_userlist.end(); ) {
		SOCKET client_temp = *iter;
		int iSendByte = send(client_temp, _T(" "), 2, 0);
		if (iSendByte == SOCKET_ERROR) {
			SOCKADDR_IN clientInfo;
			int addrlen = sizeof(clientInfo);
			getpeername(*iter, (sockaddr*)&clientInfo, &addrlen);
			printf("클라이언트[%s] 접속 종료", inet_ntoa(clientInfo.sin_addr));
			closesocket(*iter);
			g_userlist.erase(iter);
		}
		else {
			iter++;
		}
	}
}

DWORD WINAPI ClientThread(LPVOID arg)
{
	SOCKET sock = (SOCKET)arg;

	SOCKADDR_IN clientInfo;
	int addrlen = sizeof(clientInfo);
	getpeername(sock, (sockaddr*)&clientInfo, &addrlen);

	char buf[256] = { 0, };
	while (true) {
		ZeroMemory(&buf, sizeof(char) * 256);

		int iRecvByte = recv(sock, buf, 255, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			printf("클라이언트[%s] 접속 종료", inet_ntoa(clientInfo.sin_addr));
			closesocket(sock);
			return 0;
		}
		else {
			buf[iRecvByte] = 0;
			printf("\n%s", buf);

			std::list<SOCKET>::iterator iter;
			for (iter = g_userlist.begin(); iter != g_userlist.end(); iter++) {
				SOCKET client_temp = *iter;
				int iSendByte = send(client_temp, buf, (int)strlen(buf), 0);
			}
		}
	}

	return 0;
}


void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
