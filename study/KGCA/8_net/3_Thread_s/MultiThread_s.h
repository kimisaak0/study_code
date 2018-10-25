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


bool ClientAccept(SOCKET sock)
{
	NonBlockingSocket(sock, TRUE);

	SOCKADDR_IN client_addr;
	int addrlen = sizeof(client_addr);

	SOCKET client = 0;
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //Ŭ���̾�Ʈ ������ ���ο� ������ ���� ����. (����ó��)
	if (client == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			ERR_EXIT(_T("Ŭ���̾�Ʈ ���� ����"));
		}
		return false;
	}
	else {
		printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
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
			printf("Ŭ���̾�Ʈ[%s] ���� ����", inet_ntoa(clientInfo.sin_addr));
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
			printf("Ŭ���̾�Ʈ[%s] ���� ����", inet_ntoa(clientInfo.sin_addr));
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
