#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[256];
	int iRecvByte;
	int iSendByte;
	WSABUF wsabuf;
};


static void ERR_EXIT(const TCHAR* msg);

SOCKET Init();
SOCKET ClientAccept(SOCKET sock);

bool AddSI(SOCKET sock);

void RemoveSI(int index);

DWORD WINAPI WorkerThread(LPVOID arg);

void Release(SOCKET sock);

int run();