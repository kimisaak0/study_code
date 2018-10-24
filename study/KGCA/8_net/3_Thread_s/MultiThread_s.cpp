#include "MultiThread_s.h"

int main()
{
	SOCKET sock = Init();

	while (true) {
		ClientAccept(sock);
		
		DWORD dwUserThreadID;
		std::list<SOCKET>::iterator list_iter;
		HANDLE hThread = CreateThread(0, 0, ClientThread, (LPVOID)*list_iter, 0, &dwUserThreadID);
	}

	Release(sock);

}