#include <Windows.h>
#include <iostream>

DWORD WINAPI T(LPVOID arg);

int g_sum = 0;

int main()
{
	HANDLE HL[4];

	for (int i = 0; i < 4; i++) {
		HANDLE hT = CreateThread(NULL, 0, T, NULL, CREATE_SUSPENDED, NULL);
		if (hT == NULL) {
			printf("������1 ���� ���� \n");
		}

		HL[i] = hT;
	}
	

	for (int i = 0; i < 4; i++) {
		g_sum = 0;
		printf("������ ���� ��, sum = %d\n", g_sum);
		ResumeThread(HL[i]);
		WaitForSingleObject(HL[i], INFINITE);
		printf("������ ���� ��, sum = %d\n", g_sum);
	}

	for (int i = 0; i < 4; i++) {
		CloseHandle(HL[i]);
	}

	return 0;
}

DWORD WINAPI T(LPVOID arg)
{
	for (int i = 0; i < 10; i++) {
		g_sum += i;
		Sleep(100);
	}

	return 0;
}