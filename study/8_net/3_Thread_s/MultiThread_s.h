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
	setlocale(LC_ALL, "KOREAN"); // ���� ����.

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
		ERR_EXIT(_T("���� �ʱ�ȭ ����"));
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);


	SOCKADDR_IN sa_in;
	ZeroMemory(&sa_in, sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_in.sin_port = htons(10000);

	// 0) ��� ȯ�� ������ ���� ������ ����. ���� �� ������ �̿��� ���� ������ Ŭ���̾�Ʈ ������ ������. (��� �����̶�� ��)
	iRet = bind(sock, (sockaddr*)&sa_in, sizeof(sa_in));
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("���Ͽ� ��� ȯ�� ���ε� ����"));
		return -1;
	}

	// 1)Ŭ���̾�Ʈ�� ������ �� ���� ���
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("������ ���� ����"));
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
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //Ŭ���̾�Ʈ ������ ���ο� ������ ���� ����. (����ó��)
	if ((int)client != SOCKET_ERROR) {
		printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
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
			printf("Ŭ���̾�Ʈ[%s] ���� ����\n", inet_ntoa(clientInfo.sin_addr));
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
