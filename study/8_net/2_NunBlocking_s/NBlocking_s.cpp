#include "NBlocking_s.h"


int main()
{
	int iRet;

	SOCKET sock = Init();

	//소켓을 생성하고 넌블로킹 소켓으로 변환한다.
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("대기 소켓 생성 실패"));
		return -1;
	}

	ClientAccept(sock);

	int iSendSize = 0;
	int iRecvSize = 0;

	char buf[MAX_BUFFER_SIZE] = { 0, };

	while (true) {
		std::list<SOCKET>::iterator list_iter;
		for (list_iter = g_userlist.begin(); list_iter != g_userlist.end(); list_iter++) {
			SOCKET client_temp = *list_iter;
			iRecvSize = recv(client_temp, buf, MAX_BUFFER_SIZE, 0);
			if (iRecvSize != SOCKET_ERROR) {
				printf("%s \n", buf);
				std::list<SOCKET>::iterator list_iter_2;
				for (list_iter_2 = g_userlist.begin(); list_iter_2 != g_userlist.end(); list_iter_2++) {
					SOCKET client_temp = *list_iter_2;
					iSendSize = send(client_temp, buf, (int)strlen(buf), 0);
				}
			}
		}

		Sleep(1000);
	}

	printf("서버종료");
	Release(sock);

	return 0;
}