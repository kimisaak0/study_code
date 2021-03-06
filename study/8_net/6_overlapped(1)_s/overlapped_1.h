#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <tchar.h>

#pragma pack (push, 1)

struct packHead
{
	TCHAR name[30];
	WORD length;
};

struct packet
{
	packHead ph;
	TCHAR buf[256];
};

#pragma pack (pop)

struct SOCKETINFO
{
	WSAOVERLAPPED overlapped;
	SOCKET sock;
	packet pack;
	int iRecvByte;
	int iSendByte;
	WSABUF wsabuf;
};

int g_iTotalSockets = 0;
SOCKETINFO* SIArr[WSA_MAXIMUM_WAIT_EVENTS];
WSAEVENT EventArr[WSA_MAXIMUM_WAIT_EVENTS];
CRITICAL_SECTION cs;

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

int SendData(SOCKET sock, packet* pack)
{
	int iSendByte = 0;

	int iTotalSize = pack->ph.length * 2 + sizeof(packHead);

	TCHAR* pMsg = (TCHAR*)pack;

	do {
		int iSend = send(sock, (char*)&pMsg[iSendByte], iTotalSize - iSendByte, 0);
		iSendByte += iSend;
	} while (iSendByte < iTotalSize);
	
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

	_tcscpy_s(retstr, _tcslen(pack.ph.name), pack.ph.name);
	_tcscat_s(retstr, _tcslen(pack.buf), pack.buf);

	return iRecvByte + sizeof(packHead);
}

bool AddSI(SOCKET sock)
{
	EnterCriticalSection(&cs);

	if (g_iTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS) {
		std::cout << _T("[오류] g_iTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS \n");
		return false;
	}


	SOCKETINFO* pSI = new SOCKETINFO;
	if (pSI == nullptr) {
		std::cout << _T("[오류] 메모리가 부족합니다. \n");
		return false;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		std::cout << _T("[오류] hEvent == WSA_INVALID_EVENT \n");
		return false;
	}

	ZeroMemory(&pSI->overlapped, sizeof(pSI->overlapped));
	pSI->overlapped.hEvent = hEvent;
	pSI->sock = sock;
	pSI->iRecvByte = 0;
	pSI->iSendByte = 0;
	pSI->wsabuf.buf = pSI->pack.buf;
	pSI->wsabuf.len = 256;
	//ZeroMemory(pSI->buf, sizeof(char) * 256);
	SIArr[g_iTotalSockets] = pSI;
	EventArr[g_iTotalSockets] = hEvent;
	g_iTotalSockets++;

	LeaveCriticalSection(&cs);

	return true;
}

void RemoveSI(int index)
{
	EnterCriticalSection(&cs);

	SOCKETINFO* pSI = SIArr[index];

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	getpeername(pSI->sock, (SOCKADDR*)&addr, &addrlen);
	printf("접속 종료 [%s]\n", inet_ntoa(addr.sin_addr));

	closesocket(pSI->sock);
	delete pSI;
	WSACloseEvent(EventArr[index]);

	if (index != (g_iTotalSockets - 1)) {
		SIArr[index] = SIArr[g_iTotalSockets - 1];
		EventArr[index] = EventArr[g_iTotalSockets - 1];
	}

	g_iTotalSockets--;

	LeaveCriticalSection(&cs);
}

DWORD WINAPI WorkerThread(LPVOID arg)
{
	int iRet;

	while (true) {
		//이벤트 객체 관찰
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

		//클라이언트 정보 얻기
		SOCKADDR_IN addr;
		int addrlen = sizeof(addr);
		getpeername(ptr->sock, (SOCKADDR*)&addr, &addrlen);
		
		//비동기 입출력 결과 확인
		DWORD cbTransferred, flags;
		iRet = WSAGetOverlappedResult(ptr->sock, &ptr->overlapped, &cbTransferred, FALSE, &flags);
		if (iRet == FALSE || cbTransferred == 0) {
			RemoveSI(index);
			continue;
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
			ptr->overlapped.hEvent = EventArr[index];
			ptr->wsabuf.buf = ptr->buf + ptr->iSendByte;
			ptr->wsabuf.len = ptr->iRecvByte - ptr->iSendByte;

			for (int i = 1; i < g_iTotalSockets; i++) {
				DWORD sendbyte;
				iRet = WSASend(SIArr[i]->sock, &ptr->wsabuf, 1, &sendbyte, flags, &ptr->overlapped, NULL);
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
			ptr->overlapped.hEvent = EventArr[index];
			ptr->wsabuf.buf = ptr->buf;
			ptr->wsabuf.len = 256;

			DWORD recvbytes;

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

void Release(SOCKET sock)
{
	// 8)
	closesocket(sock);
	WSACleanup();
}


int run()
{
	int iRet;

	InitializeCriticalSection(&cs);

	SOCKET sock = Init();

	//더미 이벤트 객체 생성
	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		ERR_EXIT(_T("WSACreateEvent"));
		return -1;
	}
	EventArr[g_iTotalSockets++] = hEvent;

	//스레드 생성
	HANDLE hThread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);
	if (hThread == NULL) {
		ERR_EXIT(_T("스레드 생성 실패"));
		return -1;
	}
	CloseHandle(hThread);

	//데이터 통신에 사용할 변수
	SOCKET client;

	DWORD flags, recvbytes;

	while (true) {
		client = ClientAccept(sock);

		//소켓 정보 추가
		if (AddSI(client) == false) {
			printf("접속 종료[]");
			closesocket(client);
			continue;
		}

		//비동기 입출력 시작
		SOCKETINFO* pSI = SIArr[g_iTotalSockets - 1];
		flags = 0;
		iRet = WSARecv(pSI->sock, &pSI->wsabuf, 1, &recvbytes, &flags, &pSI->overlapped, NULL);
		if (iRet == SOCKET_ERROR) {
			if (WSAGetLastError() != WSA_IO_PENDING) {
				ERR_EXIT(_T("WSARecv()"));
				RemoveSI(g_iTotalSockets - 1);
				continue;
			}
		}

		//소켓 개수의 변화를 알림
		WSASetEvent(EventArr[0]);
	}

	Release(sock);
}