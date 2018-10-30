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
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	char buf[256];
	int iRecvByte;
	int iSendByte;
	WSABUF wsabuf;
};

//std::list<SOCKET> g_userlist;

int g_iTotalSockets = 0;
SOCKETINFO* SIArr[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT EventArr[WSA_MAXIMUM_WAIT_EVENTS];
CRITICAL_SECTION cs;

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
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //Ŭ���̾�Ʈ ������ ���ο� ������ ���� ����. (����ó��)
	if ((int)client != SOCKET_ERROR) {
		printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
		//g_userlist.push_back(client);
		return client;
	}

	return false;
}

DWORD WINAPI WorkerThread(LPVOID arg)
{
	int iRet;

	while (true) {
		//�̺�Ʈ ��ü ����
		DWORD index = WSAWaitForMultipleEvents(g_iTotalSockets, EventArr, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			continue;
		}
		index -= WSA_WAIT_EVENT_0;
		WSAResetEvent(EventArr[index]);
		if (index == 0) {
			continue;
		}

		SOCKETINFO* ptr = SIArr[index];

		//Ŭ���̾�Ʈ ���� ���
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);
		getpeername(ptr->sock, (SOCKADDR*)&addr, &addrlen);
		
		//�񵿱� ����� ��� Ȯ��
		DWORD cbTransferred, flags;
		iRet = WSAGetOverlappedResult(ptr->sock, &ptr->overlapped, &cbTransferred, FALSE, &flags);
		if (iRet == FALSE || cbTransferred == 0) {
			RemoveSI(index);
			printf("���� ����[%s]", inet_ntoa(addr.sin_addr));
			continue;
		}

		//������ ���۷� ����
		if (ptr->iRecvByte == 0) {
			ptr->iRecvByte = cbTransferred;
			ptr->iSendByte = 0;
			//���� ������ ���
			ptr->buf[ptr->iRecvByte] = '\0';
			printf("[%s] %s\n", inet_ntoa(addr.sin_addr), ptr->buf);
		}
		else {
			ptr->iSendByte += cbTransferred;
		}

		if (ptr->iRecvByte > ptr->iSendByte) {
			//������ ������
			ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
			ptr->overlapped.hEvent = EventArr[index];
			ptr->wsabuf.buf = ptr->buf + ptr->iSendByte;
			ptr->wsabuf.len = ptr->iRecvByte - ptr->iSendByte;

			DWORD sendbyte;
			iRet = WSASend(ptr->sock, &ptr->wsabuf, 1, &sendbyte, 0, &ptr->overlapped, NULL);
			if (iRet == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					ERR_EXIT(_T("WSASend"));
				}
				continue;
			}
		}
		else {
			ptr->iRecvByte = 0;
			//������ �ޱ�
			ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
			ptr->overlapped.hEvent = EventArr[index];
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = 256;

			DWORD recvbytes;
			flags = 0;
			iRet = WSARecv(ptr->sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, NULL);
			if (iRet == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					ERR_EXIT(_T("WSASend"));
				}
				continue;
			}
		}
	}
}


bool AddSI(SOCKET sock)
{
	if (g_iTotalSockets >= FD_SETSIZE) {
		std::cout << _T("[����] ���� ������ �߰��� �� �����ϴ�. \n");
		return false;
	}

	SOCKETINFO* pSI = new SOCKETINFO;
	if (pSI == nullptr) {
		std::cout << _T("[����] �޸𸮰� �����մϴ�. \n");
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
	strcpy(buf, inet_ntoa(addr.sin_addr));

	printf("���� ���� [%s]\n", buf);

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
