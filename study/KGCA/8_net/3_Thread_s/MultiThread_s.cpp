#include "MultiThread_s.h"

int main()
{
	SOCKET sock = Init();

	DWORD dwUserThreadID;

	while (true) {
		SOCKET client = ClientAccept(sock);
		if ((bool)client) {
			HANDLE hThread = CreateThread(0, 0, ClientThread, (SOCKET*)client, 0, &dwUserThreadID);
		}
		acceptCheck();
	}

	Release(sock);
}