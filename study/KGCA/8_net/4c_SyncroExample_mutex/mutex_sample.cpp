#include <Windows.h>
#include <iostream>


HANDLE hMutex;

int g_iNum;

//스레드가 공유 객체에 엑세스 할 수 있을때가지 대기한다는 것이 핵심이다.

DWORD WINAPI _T1(LPVOID arg)
{
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(hMutex, INFINITE); // 뮤텍스를 얻음
		g_iNum++;
		printf("T1 : [g_iNum:%d]\n", g_iNum);
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI _T2(LPVOID arg)
{
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(hMutex, INFINITE); // 뮤텍스를 얻음
		g_iNum++;
		printf("T2 : [g_iNum:%d]\n", g_iNum);
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI _T3(LPVOID arg)
{
	for (int i = 0; i < 5; i++) {
		WaitForSingleObject(hMutex, INFINITE); // 뮤텍스를 얻음
		g_iNum++;
		printf("T3 : [g_iNum:%d]\n", g_iNum);
		ReleaseMutex(hMutex);
	}

	return 0;
}



int main()
{
	hMutex = CreateMutex(NULL, FALSE, NULL); // 뮤텍스 생성
	if (hMutex == NULL) {
		printf("뮤텍스 생성 실패 \n");
		return 0;
	}

	//쓰레드 3개 생성
	HANDLE hT[3];
	hT[0] = CreateThread(NULL, 0, _T1, NULL, 0, NULL);
	hT[1] = CreateThread(NULL, 0, _T2, NULL, 0, NULL);
	hT[2] = CreateThread(NULL, 0, _T3, NULL, 0, NULL);

	WaitForMultipleObjects(3, hT, TRUE, INFINITE);

	CloseHandle(hMutex); //뮤텍스 제거

	printf("g_iNum : %d", g_iNum);

	return 0;
}