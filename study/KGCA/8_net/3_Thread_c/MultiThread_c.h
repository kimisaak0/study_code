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

bool IPConnect(SOCKET sock)
{
	int iRet = 0;

	// ���� ���� ó��
	do {
		if (iRet == SOCKET_ERROR) {
			std::cout << "IP�� �߸� �Է��ϼ̰ų�, ������ �����ֽ��ϴ�.\n";
			//return false;
		}
		std::string ip;
		std::cout << "������ IP�� �Է��ϼ���. \n";
		std::cin >> ip;

		SOCKADDR_IN sa_in;
		ZeroMemory(&sa_in, sizeof(sa_in));
		sa_in.sin_family = AF_INET;
		sa_in.sin_addr.s_addr = inet_addr(ip.c_str());     //���ڿ��� ���ڷ� ��ȯ
		sa_in.sin_port = htons(10000);                     //��Ʋ����ȿ��� �򿣵������ ��ȯ

		iRet = connect(sock, (sockaddr*)&sa_in, sizeof(sa_in));    //�Է��� IP�� ���ӽõ�.
	} while (iRet == SOCKET_ERROR);

	return true;
}

DWORD WINAPI SendThread(LPVOID arg) 
{
	SOCKET sock = (SOCKET)arg;
	char buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);

	}
}

void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
