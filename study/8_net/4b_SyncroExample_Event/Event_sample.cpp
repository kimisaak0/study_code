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
		//읽기 완료 대기
		dRet = WaitForSingleObject(hReadEvent, INFINITE);
		if (dRet != WAIT_OBJECT_0) { break; }

		//공유 버퍼에 데이터 저장
		for (int i = 0; i < BUFSIZE; i++) {
			buf[i] = k;
		}

		//쓰기 완료 알림
		SetEvent(hWriteEvent);
	}

	return 0;
}


DWORD WINAPI ReadThread(LPVOID arg)
{
	DWORD dRet;

	while(true) {
		//쓰기 완료 대기
		dRet = WaitForSingleObject(hWriteEvent, INFINITE);
		if (dRet != WAIT_OBJECT_0) { break; }

		//읽은 데이터 출력
		printf("Thread %4d : ", GetCurrentThreadId());
		for (int i = 0; i < BUFSIZE; i++) {
			printf("%3d ", buf[i]);
		}
		printf("\n");

		//버퍼초기화
		ZeroMemory(buf, sizeof(buf));

		//읽기 완료 알림
		SetEvent(hReadEvent);
	}

	return 0;
}

int main()
{
	//자동 리셋 이벤트 생성
	hWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL); //비신호 상태
	hReadEvent = CreateEvent(NULL, FALSE, TRUE, NULL); //신호 상태

	//생성 실패시 종료
	if (hWriteEvent == NULL || hReadEvent == NULL) {
		printf("이벤트 생성 실패 \n");
		return 0;
	}

	//쓰레드 3개 생성
	HANDLE hT[3];
	hT[0] = CreateThread(NULL, 0, WriteThread, NULL, 0, NULL);
	hT[1] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);
	//hT[2] = CreateThread(NULL, 0, ReadThread, NULL, 0, NULL);

	WaitForMultipleObjects(2, hT, TRUE, INFINITE);

	//이벤트 제거
	CloseHandle(hWriteEvent);
	CloseHandle(hReadEvent);

	return 0;
}