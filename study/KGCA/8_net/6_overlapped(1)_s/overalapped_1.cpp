#include "overlapped_1.h"

int main()
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