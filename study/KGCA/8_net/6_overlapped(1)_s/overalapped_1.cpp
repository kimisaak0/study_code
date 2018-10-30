#include "overlapped_1.h"

int main()
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