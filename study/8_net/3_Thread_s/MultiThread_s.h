#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

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

#define ACCEPTCHECK 0000
#define CHAT_MSG    1000

#pragma pack (push, 1)

struct packHead
{
	WORD type;
	WORD length;
};

struct packet
{
	packHead ph;
	TCHAR buf[256];
};

#pragma pack (pop)


int SendData(SOCKET sock, packet* pack)
{
	int iSendByte = 0;

	int iTotalSize = pack->ph.length*2 + sizeof(packHead);

	TCHAR* pMsg = (TCHAR*)pack;

	if (pack->ph.type == ACCEPTCHECK) {
		do {
			int iSend = send(sock, (char*)&pMsg[iSendByte], iTotalSize - iSendByte, 0);
			iSendByte += iSend;
		} while (iSendByte < iTotalSize);
		return -2;
	}
	if (pack->ph.type == CHAT_MSG) {
		do {
			int iSend = send(sock, (char*)&pMsg[iSendByte], iTotalSize - iSendByte, 0);
			iSendByte += iSend;
		} while (iSendByte < iTotalSize);
	}

	return iSendByte;
}

int RecvData(SOCKET client, TCHAR* retstr)
{
	packet pack;
	ZeroMemory(&pack, sizeof(pack));

	TCHAR buf[256] = { 0, };
	int iRecvByte = 0;
	int iRecv = 0;

	iRecv = recv(client, (char*)&buf[iRecvByte], sizeof(packHead) - iRecvByte, 0);
	iRecvByte += iRecv;

	if (iRecvByte == sizeof(packHead)) {
		memcpy(&pack.ph, buf, sizeof(packHead));
	}


	TCHAR strBuf[256] = { 0, };

	do {
		iRecv = recv(client, (char*)strBuf, pack.ph.length*2, 0);
		if (iRecv == -1) {
			return - 1;
		}
		iRecvByte += iRecv;
	} while (iRecvByte < pack.ph.length*2);
	
	switch (pack.ph.type) {
		case ACCEPTCHECK: {
			return -2;
		} break;
		case CHAT_MSG: {
			memcpy(retstr, strBuf, pack.ph.length*2);
		} break;
	}

	return iRecvByte;
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


SOCKET ClientAccept(SOCKET sock)
{
	NonBlockingSocket(sock, TRUE);

	SOCKADDR_IN client_addr;
	int addrlen = sizeof(client_addr);

	SOCKET client = 0;
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //클라이언트 정보를 새로운 소켓을 만들어서 저장. (연결처리)
	if ((int)client != SOCKET_ERROR) {
		printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
		g_userlist.push_back(client);
		return client;
	}
	NonBlockingSocket(sock, FALSE);
	return false;
	
}

void acceptCheck()
{
	std::list<SOCKET>::iterator iter;
	for (iter = g_userlist.begin(); iter != g_userlist.end(); ) {
		SOCKET client_temp = *iter;
		packHead ph = { ACCEPTCHECK, 0 };
		packet pack = { ph, _T("") };
		int iSendByte = SendData(client_temp, &pack);
		if (iSendByte == SOCKET_ERROR) {
			SOCKADDR_IN clientInfo;
			int addrlen = sizeof(clientInfo);
			getpeername(*iter, (sockaddr*)&clientInfo, &addrlen);
			printf("클라이언트[%s] 접속 종료\n", inet_ntoa(clientInfo.sin_addr));
			closesocket(*iter);
			g_userlist.erase(iter);
			break;
		}
		else {
			iter++;
		}
	}
}

DWORD WINAPI ClientThread(LPVOID arg)
{
	SOCKET client = (SOCKET)arg;

	SOCKADDR_IN clientInfo;
	int addrlen = sizeof(clientInfo);
	getpeername(client, (sockaddr*)&clientInfo, &addrlen);

	TCHAR recvBuf[256] = { 0, };
	while (true) {
		Sleep(1);
		ZeroMemory(&recvBuf, sizeof(char) * 256);
		int iRecvResult = RecvData(client, recvBuf);
		if (iRecvResult > 0) {
			_tprintf(_T("%s\n"), recvBuf);
			std::list<SOCKET>::iterator iter;
			for (iter = g_userlist.begin(); iter != g_userlist.end(); iter++) {
				SOCKET client_temp = *iter;
				packHead ph = { CHAT_MSG, (WORD)_tcslen(recvBuf) };
				packet pack;
				pack.ph = ph;
				_tcscpy_s(pack.buf, recvBuf);
				SendData(client_temp, &pack);
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
