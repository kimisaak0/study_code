#include "MultiThread_s.h"

int main()
{
	SOCKET sock = Init();

	DWORD dwUserThreadID;
	std::list<SOCKET>::iterator list_iter;

	while (true) {
		if (ClientAccept(sock)) {
			HANDLE hThread = CreateThread(0, 0, ClientThread, (LPVOID)*list_iter, 0, &dwUserThreadID);
		}
	}

	Release(sock);
}