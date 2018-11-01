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
		iRecvTotal += iRecv;
	} while (iRecvTotal < sizeof(packHead));
	if (iRecvTotal == 0 || iRecvTotal == SOCKET_ERROR) {
		return iRecvTotal;
	}

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

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) {
		ERR_EXIT(L"���� �ʱ�ȭ ����");
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
	char buf[256] = { 0, };
	while (true) {
		ZeroMemory(buf, sizeof(char) * 256);
		fgets(buf, 256, stdin);
		if (buf[strlen(buf) - 1] == '\n') {
			buf[strlen(buf) - 1] = 0;
		}
		if (strlen(buf) == 0) { 
			printf("�����մϴ�.\n");
			break;
		} // ���ʹ� ����!
		
		packHead ph = { CHAT_MSG, strlen(buf) };
		packet pack;
		pack.ph = ph;
		strcpy_s(pack.buf, buf);

		int iSendByte = SendData(sock, &pack);
		if (iSendByte == SOCKET_ERROR) { 
			printf("������ �������ϴ� \n");
			break;
		}
		printf("���� [%d] \n", iSendByte);
	}
	return 0;
}

void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
