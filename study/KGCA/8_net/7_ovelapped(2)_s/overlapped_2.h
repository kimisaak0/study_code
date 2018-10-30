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
	setlocale(LC_ALL, "KOREAN"); // 지역 설정.

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
		ERR_EXIT(_T("윈속 초기화 실패"));
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa_in;
	ZeroMemory(&sa_in, sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_in.sin_port = htons(10000);

	// 0) 통신 환경 정보를 갖는 소켓을 생성. 이후 이 소켓을 이용해 실제 접속한 클라이언트 소켓을 생성함. (대기 소켓이라는 뜻)
	iRet = bind(sock, (sockaddr*)&sa_in, sizeof(sa_in));
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("소켓에 통신 환경 바인딩 실패"));
		return -1;
	}

	// 1)클라이언트가 접속할 때 까지 대기
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("대기상태 설정 실패"));
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
	client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //클라이언트 정보를 새로운 소켓을 만들어서 저장. (연결처리)
	if ((int)client != SOCKET_ERROR) {
		printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
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
	//접속한 클라이언트 정보 출력
	ClientAccept(sock);
	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	getpeername(sock, (SOCKADDR*)&addr, &addrlen);
	printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(addr.sin_addr));

	SOCKETINFO* pSI = new SOCKETINFO;
	if (pSI == nullptr) {
		std::cout << _T("[오류] 메모리가 부족합니다. \n");
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
	printf("접속 종료 [%s]\n", inet_ntoa(addr.sin_addr));

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

	//비동기 입출력 결과 확인
	if (dwErr != 0 || cbTransferred == 0) {
		if (dwErr != 0) {
			ERR_EXIT(_T("Error"));
		}
		closesocket(ptr->sock);
		printf("접속 종료 [%s]", inet_ntoa(addr.sin_addr));
		delete ptr;
		return;
	}

	//데이터 전송량 갱신
	if (ptr->iRecvByte == 0) {
		ptr->iRecvByte = cbTransferred;
		ptr->iSendByte = 0;
		//받은 데이터 출력
		ptr->buf[ptr->iRecvByte] = '\0';
		printf("[%s] %s\n", inet_ntoa(addr.sin_addr), ptr->buf);
	}
	else {
		ptr->iSendByte += cbTransferred;
	}

	if (ptr->iRecvByte > ptr->iSendByte) {
		//데이터 보내기
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
		//데이터 받기
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
					//새로운 클라이언트가 접속한 경우
					AddSI(sock);
					break;
				}
			}
			if (result == WAIT_IO_COMPLETION) {
				continue;
			}
		}

		DWORD recvByte, flags = 0;
		
		//비동기 입출력 시작
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
