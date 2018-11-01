#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>
//#include <list>

struct SOCKETINFO
{
	SOCKET sock;
	char buf[256];
	int iRecvByte;
	int iSendByte;
};

//std::list<SOCKET> g_userlist;

int g_iTotalSockets = 0;
SOCKETINFO* SIArr[FD_SETSIZE];

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

static int NonBlockingSocket(SOCKET sock, u_long uMode)
{
	//To make NonBlocking Socket, controls the I/O mode of a socket
	int iRet = ioctlsocket(sock, FIONBIO, &uMode);
	if (iRet != NO_ERROR) {
		ERR_EXIT(_T("ioctlsocket"));
	}
	return iRet;
}


SOCKET ClientAccept(SOCKET sock)
{
	SOCKADDR_IN client_addr;
	int addrlen = sizeof(client_addr);

	SOCKET client = 0;
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //클라이언트 정보를 새로운 소켓을 만들어서 저장. (연결처리)
	if ((int)client != SOCKET_ERROR) {
		printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
		//g_userlist.push_back(client);
		return client;
	}

	return false;
}



bool AddSI(SOCKET sock)
{
	if (g_iTotalSockets >= FD_SETSIZE) {
		std::cout << _T("[오류] 소켓 정보를 추가할 수 없습니다. \n");
		return false;
	}

	SOCKETINFO* pSI = new SOCKETINFO;
	if (pSI == nullptr) {
		std::cout << _T("[오류] 메모리가 부족합니다. \n");
		return false;
	}

	//ZeroMemory(&pSI, sizeof(pSI));
	pSI->sock = sock;
	ZeroMemory(pSI->buf, sizeof(char) * 256);
	pSI->iRecvByte = 0;
	pSI->iSendByte = 0;

	SIArr[g_iTotalSockets++] = pSI;

	return true;
}

void RemoveSI(int index)
{
	SOCKETINFO* pSI = SIArr[index];

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	getpeername(pSI->sock, (SOCKADDR*)&addr, &addrlen);

	char buf[30] = { 0, };
	strcpy(buf,inet_ntoa(addr.sin_addr));

	printf("접속 종료 [%s]\n", buf);

	closesocket(pSI->sock);
	delete pSI;

	if (index != (g_iTotalSockets - 1)) {
		SIArr[index] = SIArr[g_iTotalSockets - 1];
	}

	g_iTotalSockets--;
}

void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
