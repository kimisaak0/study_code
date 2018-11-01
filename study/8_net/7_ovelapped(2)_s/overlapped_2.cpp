#include "overlapped_2.h"

//대충 되었는데 고치기 귀찮...

int main()
{
	SOCKET sock = Init();

	//이벤트 객체 생성
	hREvent = CreateEvent(NULL, FALSE, TRUE, NULL); //자동 리셋, 신호 상태로 시작
	if (hREvent == NULL) { return -1; }
	hWEvent = CreateEvent(NULL, FALSE, FALSE, NULL); //자동 리셋, 비신호 상태로 시작
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
		client = accept(sock, NULL, NULL);
		if (client == INVALID_SOCKET) {
			ERR_EXIT(_T("accept"));
			break;
		}
		SetEvent(hWEvent);
	}

	Release(sock);
}