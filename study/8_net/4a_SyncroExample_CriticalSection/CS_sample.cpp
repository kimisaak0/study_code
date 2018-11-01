#include <Windows.h>
#include <iostream>

#define MAXCNT 100000000

int g_count = 0;

CRITICAL_SECTION cs;

DWORD WINAPI T1(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++) {
		EnterCriticalSection(&cs);
		g_count += 1;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI T2(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++) {
		EnterCriticalSection(&cs);
		g_count -= 1;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int main()
{
	InitializeCriticalSection(&cs);

	HANDLE hT[2];
	hT[0] = CreateThread(NULL, 0, T1, NULL, 0, NULL);
	hT[1] = CreateThread(NULL, 0, T2, NULL, 0, NULL);

	WaitForMultipleObjects(2, hT, TRUE, INFINITE);

	DeleteCriticalSection(&cs);

	printf("g_count = %d\n", g_count);
	
	return 0;
}