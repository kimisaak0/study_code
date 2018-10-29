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
		iRecv = recv(client, (char*)strBuf, pack.ph.length * 2, 0);
		if (iRecv == -1) {
			return -1;
		}
		iRecvByte += iRecv;
	} while (iRecvByte < pack.ph.length * 2);

	switch (pack.ph.type) {
		case ACCEPTCHECK: {
			return -2;
		} break;
		case CHAT_MSG: {
			memcpy(retstr, strBuf, pack.ph.length * 2);
		} break;
	}

	return iRecvByte;
}

SOCKET Init()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) {
		ERR_EXIT(_T("���� �ʱ�ȭ ����"));
		return -1;
	}

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		ERR_EXIT(_T("���� ���� ����"));
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
	TCHAR buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		_fgetts(buf, 256, stdin);
		if (buf[_tcslen(buf) - 1] == '\n') {
			buf[_tcslen(buf) - 1] = 0;
		}
		if (_tcslen(buf) == 0) {
			printf("�����մϴ�.\n");
			break;
		} // ���ʹ� ����!
		
		packHead ph = { CHAT_MSG, (WORD)_tcslen(buf) };
		packet pack;
		pack.ph = ph;
		_tcscpy_s(pack.buf, buf);

		int iSendByte = SendData(sock, &pack);
		if (iSendByte == SOCKET_ERROR) { 
			printf("������ �������ϴ� \n");
			break;
		}
		//printf("���� [%d] \n", iSendByte);
	}
	return 0;
}

void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
