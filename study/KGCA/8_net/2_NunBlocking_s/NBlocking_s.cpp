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

	//소켓을 생성하고 넌블로킹 소켓으로 변환한다.
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

	std::list<SOCKET> userlist;
	

	char buf[MAX_BUFFER_SIZE] = "안녕";
	int iSendSize = 0;
	int iRecvSize = 0;

	while (true) {
		SOCKADDR_IN client_addr;
		int addrlen = sizeof(client_addr);

		SOCKET client = 0;
		client = accept(sock, (SOCKADDR*)&client_addr, &addrlen);  //클라이언트 정보를 새로운 소켓을 만들어서 저장. (연결처리)
		if (client == SOCKET_ERROR) {
			if (WSAGetLastError() != WSAEWOULDBLOCK) {
				ERR_EXIT(_T("클라이언트 연결 실패"));
			}
		}
		else {
			printf("클라이언트 접속 [ip:%s]\n", inet_ntoa(client_addr.sin_addr));
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

	printf("서버종료");
	// 8)
	closesocket(sock);
	WSACleanup();
	return 0;
}