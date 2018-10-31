#include "6_overlapped(1)_lib.h"

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
	EnterCriticalSection(&cs);

	if (g_iTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS) {
		std::cout << _T("[����] g_iTotalSockets >= WSA_MAXIMUM_WAIT_EVENTS \n");
		return false;
	}


	SOCKETINFO* pSI = new SOCKETINFO;
	if (pSI == nullptr) {
		std::cout << _T("[����] �޸𸮰� �����մϴ�. \n");
		return false;
	}

	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		std::cout << _T("[����] hEvent == WSA_INVALID_EVENT \n");
		return false;
	}

	ZeroMemory(&pSI->overlapped, sizeof(pSI->overlapped));
	pSI->overlapped.hEvent = hEvent;
	pSI->sock = sock;
	pSI->iRecvByte = 0;
	pSI->iSendByte = 0;
	pSI->wsabuf.buf = pSI->buf;
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
	printf("���� ���� [%s]\n", inet_ntoa(addr.sin_addr));

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
			//������ �ޱ�
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

	//���� �̺�Ʈ ��ü ����
	WSAEVENT hEvent = WSACreateEvent();
	if (hEvent == WSA_INVALID_EVENT) {
		ERR_EXIT(_T("WSACreateEvent"));
		return -1;
	}
	EventArr[g_iTotalSockets++] = hEvent;

	//������ ����
	HANDLE hThread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);
	if (hThread == NULL) {
		ERR_EXIT(_T("������ ���� ����"));
		return -1;
	}
	CloseHandle(hThread);

	//������ ��ſ� ����� ����
	SOCKET client;

	DWORD flags, recvbytes;

	while (true) {
		client = ClientAccept(sock);

		//���� ���� �߰�
		if (AddSI(client) == false) {
			printf("���� ����[]");
			closesocket(client);
			continue;
		}

		//�񵿱� ����� ����
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

		//���� ������ ��ȭ�� �˸�
		WSASetEvent(EventArr[0]);
	}

	Release(sock);
}