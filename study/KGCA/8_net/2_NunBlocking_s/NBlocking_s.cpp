#include "NBlocking_s.h"

int main()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) { 
		ERR_EXIT(_T("���� �ʱ�ȭ ����"));
		return -1;	
	}

	//������ �����ϰ� �ͺ��ŷ �������� ��ȯ�Ѵ�.
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("��� ���� ���� ����"));
		return -1;
	}

	SOCKADDR_IN sa_in;
	ZeroMemory(&sa_in, sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_in.sin_port = htons(10000);

	// 0) ��� ȯ�� ������ ���� ������ ����. ���� �� ������ �̿��� ���� ������ Ŭ���̾�Ʈ ������ ������. (��� �����̶�� ��)
	iRet = bind(sock, (sockaddr*)&sa_in, sizeof(sa_in));
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("���Ͽ� ��� ȯ�� ���ε� ����"));
		return -1;
	}

	// 1)Ŭ���̾�Ʈ�� ������ �� ���� ���
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("������ ���� ����"));
		return -1;
	}

	std::list<SOCKET> userlist;
	

	char buf[MAX_BUFFER_SIZE] = "�ȳ�";
	int iSendSize = 0;
	int iRecvSize = 0;

	while (true) {
		SOCKADDR_IN client_addr;
		int addrlen = sizeof(client_addr);

		SOCKET client = 0;
		client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //Ŭ���̾�Ʈ ������ ���ο� ������ ���� ����. (����ó��)
		if (client == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				ERR_EXIT(_T("Ŭ���̾�Ʈ ���� ����"));
			}
		}
		else {
			printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
			userlist.push_back(client);
		}
			
		std::list<SOCKET>::iterator list_iter;
		for (list_iter = userlist.begin(); list_iter != userlist.end(); list_iter++) {
			SOCKET client_temp = *list_iter;
			iSendSize = send(client_temp, buf, strlen(buf), 0);
			//if (iSendSize == SOCKET_ERROR) {
			//	if (GetLastError() != WSAEWOULDBLOCK) {
			//		closesocket(client_temp);
			//		userlist.erase(list_iter);
			//		continue;
			//	}
			//}
		}

		for (list_iter = userlist.begin(); list_iter != userlist.end(); list_iter++) {
			SOCKET client_temp = *list_iter;
			iRecvSize = recv(client_temp, buf, MAX_BUFFER_SIZE, 0);
			//if (iRecvSize == SOCKET_ERROR) {
			//	if (GetLastError() != WSAEWOULDBLOCK) {
			//		closesocket(client_temp);
			//		userlist.erase(list_iter);
			//		continue;
			//	}
			//}
		}

		Sleep(1000);
	}

	printf("��������");
	// 8)
	closesocket(sock);
	WSACleanup();
	return 0;
}