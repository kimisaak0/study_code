#include "overlapped_2.h"

//���� �Ǿ��µ� ��ġ�� ����...

int main()
{
	SOCKET sock = Init();

	//�̺�Ʈ ��ü ����
	hREvent = CreateEvent(NULL, FALSE, TRUE, NULL); //�ڵ� ����, ��ȣ ���·� ����
	if (hREvent == NULL) { return -1; }
	hWEvent = CreateEvent(NULL, FALSE, FALSE, NULL); //�ڵ� ����, ���ȣ ���·� ����
	if (hREvent == NULL) { return -1; }


	//������ ����
	HANDLE hThread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);
	if (hThread == NULL) {
		ERR_EXIT(_T("������ ���� ����"));
		return -1;
	}
	CloseHandle(hThread);

	//������ ��ſ� ����� ����
	while (true) {
		WaitForSingleObject(hREvent, INFINITE);
		client = accept(sock, NULL, NULL);
		if (client == INVALID_SOCKET) {
			ERR_EXIT(_T("accept"));
			break;
		}
		SetEvent(hWEvent);
	}

	Release(sock);
}