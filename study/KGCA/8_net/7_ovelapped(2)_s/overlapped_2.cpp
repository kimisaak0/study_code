#include "overlapped_2.h"

int main()
{
	SOCKET sock = Init();

	//이벤트 객체 생성
	hREvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	if (hREvent == NULL) { return -1; }
	hWEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hREvent == NULL) { return -1; }


	//스레드 생성
	HANDLE hThread = CreateThread(NULL, 0, WorkerThread, NULL, 0, NULL);
	if (hThread == NULL) {
		ERR_EXIT(_T("스레드 생성 실패"));
		return -1;
	}
	CloseHandle(hThread);

	//데이터 통신에 사용할 변수
	while (true) {
		WaitForSingleObject(hREvent, INFINITE);
		SetEvent(hWEvent);
	}

	Release(sock);
}