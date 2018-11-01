#include <Windows.h>
#include <iostream>


HANDLE hMutex;

int g_iNum;

//�����尡 ���� ��ü�� ������ �� �� ���������� ����Ѵٴ� ���� �ٽ��̴�.

DWORD WINAPI _T1(LPVOID arg)
{
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(hMutex, INFINITE); // ���ؽ��� ����
		g_iNum++;
		printf("T1 : [g_iNum:%d]\n", g_iNum);
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI _T2(LPVOID arg)
{
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(hMutex, INFINITE); // ���ؽ��� ����
		g_iNum++;
		printf("T2 : [g_iNum:%d]\n", g_iNum);
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI _T3(LPVOID arg)
{
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(hMutex, INFINITE); // ���ؽ��� ����
		g_iNum++;
		printf("T3 : [g_iNum:%d]\n", g_iNum);
		ReleaseMutex(hMutex);
	}

	return 0;
}



int main()
{
	hMutex = CreateMutex(NULL, FALSE, NULL); // ���ؽ� ����
	if (hMutex == NULL) {
		printf("���ؽ� ���� ���� \n");
		return 0;
	}

	//������ 3�� ����
	HANDLE hT[3];
	hT[0] = CreateThread(NULL, 0, _T1, NULL, 0, NULL);
	hT[1] = CreateThread(NULL, 0, _T2, NULL, 0, NULL);
	hT[2] = CreateThread(NULL, 0, _T3, NULL, 0, NULL);

	WaitForMultipleObjects(3, hT, TRUE, INFINITE);

	CloseHandle(hMutex); //���ؽ� ����

	printf("g_iNum : %d", g_iNum);

	return 0;
}