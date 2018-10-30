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
SOCKETINFO** SIArr;

HANDLE hREvent, hWEvent;


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

//static int NonBlockingSocket(SOCKET sock, u_long uMode)
//{
//	//To make NonBlocking Socket, controls the I/O mode of a socket
//	int iRet = ioctlsocket(sock, FIONBIO, &uMode);
//	if (iRet != NO_ERROR) {
//		ERR_EXIT(_T("ioctlsocket"));
//	}
//	return iRet;
//}


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
	else if (client == INVALID_SOCKET) {
		ERR_EXIT(_T("Accept Error"));
		return false;
	}
}

bool AddSI(SOCKET sock)
{
	//������ Ŭ���̾�Ʈ ���� ���
	ClientAccept(sock);
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	getpeername(sock, (SOCKADDR*)&addr, &addrlen);
	printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(addr.sin_addr));

	SOCKETINFO* pSI = new SOCKETINFO;
	if (pSI == nullptr) {
		std::cout << _T("[����] �޸𸮰� �����մϴ�. \n");
		return false;
	}

	ZeroMemory(&pSI->overlapped, sizeof(pSI->overlapped));
	pSI->sock = sock;
	pSI->iRecvByte = 0;
	pSI->iSendByte = 0;
	pSI->wsabuf.buf = pSI->buf;
	pSI->wsabuf.len = 256;
	//ZeroMemory(pSI->buf, sizeof(char) * 256);
	SIArr[g_iTotalSockets] = pSI;

	return true;
}

void RemoveSI(int index)
{
	SOCKETINFO* pSI = SIArr[index];

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	getpeername(pSI->sock, (SOCKADDR*)&addr, &addrlen);
	printf("���� ���� [%s]\n", inet_ntoa(addr.sin_addr));

	closesocket(pSI->sock);
	delete pSI;

	if (index != (g_iTotalSockets - 1)) {
		SIArr[index] = SIArr[g_iTotalSockets - 1];
	}
	
	g_iTotalSockets--;

}

void CALLBACK CR(DWORD dwErr, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	int iRet;

	DWORD recvbytes, flags = 0;

	SOCKETINFO *ptr = (SOCKETINFO*)lpOverlapped;
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	getpeername(ptr->sock, (SOCKADDR*)&addr, &addrlen);

	//�񵿱� ����� ��� Ȯ��
	if (dwErr != 0 || cbTransferred == 0) {
		if (dwErr != 0) {
			ERR_EXIT(_T("Error"));
		}
		closesocket(ptr->sock);
		printf("���� ���� [%s]", inet_ntoa(addr.sin_addr));
		delete ptr;
		return;
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
		ptr->wsabuf.buf = ptr->buf + ptr->iSendByte;
		ptr->wsabuf.len = ptr->iRecvByte - ptr->iSendByte;

		for (int i = 1; i < g_iTotalSockets; i++) {
			DWORD sendbyte;
			iRet = WSASend(SIArr[i]->sock, &ptr->wsabuf, 1, &sendbyte, flags, &ptr->overlapped, CR);
			if (iRet == SOCKET_ERROR) {
				if (WSAGetLastError() != WSA_IO_PENDING) {
					ERR_EXIT(_T("WSASend"));
				}
				continue;
			}
		}
	}
	else {
		ptr->iRecvByte = 0;
		//������ �ޱ�
		ZeroMemory(&ptr->overlapped, sizeof(ptr->overlapped));
		ptr->wsabuf.buf = ptr->buf;
		ptr->wsabuf.len = 256;



		iRet = WSARecv(ptr->sock, &ptr->wsabuf, 1, &recvbytes, &flags, &ptr->overlapped, CR);
		if (iRet == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				ERR_EXIT(_T("WSASend"));
			return;
			}
		}
	}
}

DWORD WINAPI WorkerThread(LPVOID arg)
{
	int iRet;

	SOCKET sock = (SOCKET)arg;

	while (true) {
		while (true) {
			//alertable wait
			DWORD result = WaitForSingleObjectEx(hWEvent, INFINITE, TRUE);
			if (result == WAIT_OBJECT_0) {
				if (sock != 0) {
					//���ο� Ŭ���̾�Ʈ�� ������ ���
					AddSI(sock);
					break;
				}
			}
			if (result == WAIT_IO_COMPLETION) {
				continue;
			}
		}

		DWORD recvByte, flags = 0;
		
		//�񵿱� ����� ����
		iRet = WSARecv(SIArr[g_iTotalSockets]->sock, &SIArr[g_iTotalSockets]->wsabuf, 1, &recvByte, &flags, &SIArr[g_iTotalSockets]->overlapped, CR);
		if (iRet == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				ERR_EXIT(_T("WSARecv"));
				return -1;
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
