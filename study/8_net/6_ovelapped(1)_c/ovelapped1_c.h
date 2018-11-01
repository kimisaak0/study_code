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
		//�޽��� ����
		char sendBuf[256] = { 0, };
		ZeroMemory(sendBuf, sizeof(sendBuf));
		std::cout << "�Է� : "; fgets(sendBuf, 256, stdin);

		if (sendBuf[0] == '\n') {
			printf("�����մϴ�.\n");
			break; 
		} //���͸� ġ�� �����Ű��.

		size_t iLen = strlen(sendBuf);
		if (sendBuf[iLen - 1] == '\n') {
			sendBuf[iLen - 1] = '\0';
		}

		int iSendByte = 0;
		iSendByte = send(sock, sendBuf, (int)iLen, 0);  //������ ���� �Լ�
		if (iSendByte == SOCKET_ERROR) {
			printf("������ �������ϴ� \n");
			break;
		}
		std::cout << iSendByte << "byte ����. \n";
	}
	return 0;
}

int RecvData(SOCKET client, TCHAR* retstr, int len)
{
	int left = len;

	TCHAR* ptr = retstr;

	while (left > 0) {
		int iRecv = recv(client, (char*)ptr, len, 0);
		if (iRecv == SOCKET_ERROR) {
			ERR_EXIT(_T("���ú� ���� ����"));
			return -1;
		}
		else if (iRecv == 0) {
			break;
		}
		left -= iRecv;
		ptr += iRecv;
	}

	return len - left;
}


void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}
