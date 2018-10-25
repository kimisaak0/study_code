#include "MultiThread_s.h"

int main()
{
	SOCKET sock = Init();

	DWORD dwUserThreadID;

	while (true) {
		if (ClientAccept(sock)) {
			HANDLE hThread = CreateThread(0, 0, ClientThread, (SOCKET*)sock, 0, &dwUserThreadID);
		}
		acceptCheck();
	}

	Release(sock);
}