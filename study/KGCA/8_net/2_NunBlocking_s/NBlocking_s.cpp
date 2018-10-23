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


	int iUserCnt = 0;
	SOCKET client;
	std::list<SOCKET> userlist;
	SOCKADDR_IN client_addr;

	while (iUserCnt < g_MaxUser) {
		int addrlen = sizeof(client_addr);

		// 4)
		client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);
		if (client == SOCKET_ERROR) {
			//������ ������ ��쿡 ����(WSAEWOULDBLOCK)�̶�� �������� ��ȯ�̴�.
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				ERR_EXIT(_T("accept"));
				break;
			}
		}
		else {
			iRet = NonBlockingSocket(sock, TRUE);
			if (iRet == SOCKET_ERROR) { return -1; }

			char ip[INET_ADDRSTRLEN];
			printf("[ip : %s]", inet_ntop(AF_INET, &(client_addr.sin_addr), ip, INET_ADDRSTRLEN));

			userlist.push_back(client);
			iUserCnt++;
		}
	}

	char buf[MAX_BUFFER_SIZE] = { 0, };
	
	while (userlist.size() > 0) {
		ZeroMemory(buf, sizeof(char)*MAX_BUFFER_SIZE);

		std::list<SOCKET>::iterator list_iter;
		int iRecvSize;
		for (list_iter = userlist.begin(); list_iter != userlist.end(); list_iter++) {
			SOCKET client_temp = *list_iter;
			// 5)
			iRecvSize = recv(client_temp, buf, MAX_BUFFER_SIZE - 1, 0);
			
			if (iRecvSize == 0) {
				char ip[INET_ADDRSTRLEN];
				printf("EXIT! [ip : %s]", inet_ntop(AF_INET, &(client_addr.sin_addr), ip, INET_ADDRSTRLEN));
				closesocket(client_temp);
				userlist.erase(list_iter);
				break; //����Ʈ�� ������ �߰��� ����Ǿ����Ƿ�
			}

			if (iRecvSize == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					//ġ������ ����
					ERR_EXIT(_T("recv"));
					closesocket(client_temp);
					userlist.erase(list_iter);
					break;
				}
			}

			if (iRecvSize > 0) {
				break;
			}
		}

		if (strlen(buf) > 0) {
			printf("%s", buf);
			int iSendSize;
			for (list_iter = userlist.begin(); list_iter != userlist.end(); list_iter++) {
				SOCKET client_temp = *list_iter;
				// 6)
				iSendSize = send(client_temp, buf, MAX_BUFFER_SIZE - 1, 0);
				if (iSendSize == SOCKET_ERROR) {
					ERR_EXIT(_T("send"));
					closesocket(client_temp);
					userlist.erase(list_iter);
					break;
				}
			}
		}
		Sleep(1);
	}
	printf("��������");
	// 8)
	closesocket(sock);
	WSACleanup();
	return 0;
}