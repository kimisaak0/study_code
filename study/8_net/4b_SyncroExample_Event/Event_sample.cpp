#include <Windows.h>
#include <iostream>

#define BUFSIZE 10

HANDLE hReadEvent;
HANDLE hWriteEvent;
int buf[BUFSIZE];

DWORD WINAPI WriteThread(LPVOID arg)
{
	DWORD dRet;

	for (int k = 0; k < 500; k++) {
		//�б� �Ϸ� ���
		dRet = WaitForSingleObject(hReadEvent, INFINITE);
		if (dRet != WAIT_OBJECT_0) { break; }

		//���� ���ۿ� ������ ����
		for (int i = 0; i < BUFSIZE; i++) {
			buf[i] = k;
		}

		//���� �Ϸ� �˸�
		SetEvent(hWriteEvent);
	}

	return 0;
}


DWORD WINAPI ReadThread(LPVOID arg)
{
	DWORD dRet;

	while(true) {
		//���� �Ϸ� ���
		dRet = WaitForSingleObject(hWriteEvent, INFINITE);
		if (dRet != WAIT_OBJECT_0) { break; }

		//���� ������ ���
		printf("Thread %4d : ", GetCurrentThreadId());
		for (int i = 0; i < BUFSIZE; i++) {
			printf("%3d ", buf[i]);
		}
		printf("\n");

		//�����ʱ�ȭ
		ZeroMemory(buf, sizeof(buf));

		//�б� �Ϸ� �˸�
		SetEvent(hReadEvent);
	}

	return 0;
}

int main()
{
	//�ڵ� ���� �̺�Ʈ ����
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL); //���ȣ ����
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL); //��ȣ ����

	//���� ���н� ����
	if (hWriteEvent == NULL || hReadEvent == NULL) {
		printf("�̺�Ʈ ���� ���� \n");
		return 0;
	}

	//������ 3�� ����
	HANDLE hT[3];
	hT[0] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	hT[1] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
	//hT[2] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);

	WaitForMultipleObjects(2, hT, TRUE, INFINITE);

	//�̺�Ʈ ����
	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	return 0;
}