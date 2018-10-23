#include "NBlocking_s.h"

int main()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if (iRet != (int)NO_ERROR) { 
		ERR_EXIT(_T("윈속 초기화 실패"));
		return -1;	
	}

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("대기 소켓 생성 실패"));
		return -1;
	}

	SOCKADDR_IN sa_in;
	ZeroMemory(&sa_in, sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_addr.s_addr = htonl(INADDR_ANY);
	sa_in.sin_port = htons(10000);

	// 0) 통신 환경 정보를 갖는 소켓을 생성. 이후 이 소켓을 이용해 실제 접속한 클라이언트 소켓을 생성함. (대기 소켓이라는 뜻)
	iRet = bind(sock, (sockaddr*)&sa_in, sizeof(sa_in));
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("소켓에 통신 환경 바인딩 실패"));
		return -1;
	}

	// 1)클라이언트가 접속할 때 까지 대기
	iRet = listen(sock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) {
		ERR_EXIT(_T("대기상태 설정 실패"));
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
			//논블록형 소켓일 경우에 오류(WSAEWOULDBLOCK)이라면 정상적인 반환이다.
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
				break; //리스트의 갯수가 중간에 변경되었으므로
			}

			if (iRecvSize == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					//치명적인 오류
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
	printf("서버종료");
	// 8)
	closesocket(sock);
	WSACleanup();
	return 0;
}