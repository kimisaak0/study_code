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
	if (pack->ph.type == ACCEPTCHECK) {
		do {
			int iSend = send(sock, (char*)pack, sizeof(packet) - iSendTotal, 0);
			iSendTotal += iSend;
		} while (iSendTotal < sizeof(packet));
		return -2;
	}

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
		if (iRecv == 0 || iRecv == SOCKET_ERROR) {
			return iRecv;
		}
		iRecvTotal += iRecv;
	} while (iRecvTotal < sizeof(packHead));

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
		packet pack = { ph, "" };
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

	char recvBuf[256] = { 0, };
	while (true) {
		ZeroMemory(&recvBuf, sizeof(char) * 256);
		int iRecvByte = RecvData(client, recvBuf);
		if (iRecvByte > 0) {
			printf("\n%s", recvBuf);
			std::list<SOCKET>::iterator iter;
			for (iter = g_userlist.begin(); iter != g_userlist.end(); iter++) {
				SOCKET client_temp = *iter;
				packHead ph = { CHAT_MSG, strlen(recvBuf) };
				packet pack;
				pack.ph = ph;
				strcpy_s(pack.buf, recvBuf);
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
