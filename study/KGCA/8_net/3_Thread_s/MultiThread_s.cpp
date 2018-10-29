#include "MultiThread_s.h"

int main()
{
	SOCKET sock = Init();

	DWORD dwUserThreadID;

	while (true) {
		//acceptCheck();
		SOCKET client = ClientAccept(sock);
		HANDLE hThread = 0;
		if ((bool)client) {
			hThread = CreateThread(0, 0, ClientThread, (SOCKET*)client, 0, &dwUserThreadID);
		}
	}

	Release(sock);
}