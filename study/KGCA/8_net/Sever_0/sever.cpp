#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32")

#include <vector>

std::vector<SOCKET> clientList;
//서버

int main()
{
	WSADATA wd;
	//윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
		return 1;
	}

	//소켓 생성 (TCP로 생성함)
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		return 1;
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = inet_addr("192.168.0.104");
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(10000);
	//호스트 정렬(리틀엔디안)에서 네트워크 정렬(빅엔디안).

	//서버와 클라이언트 연결
	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	//이벤트 처리 요청
	ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	u_long on = TRUE;
	ioctlsocket(sock, FIONBIO, &on);

	SOCKET clientSock;
	SOCKADDR_IN clientInfo;
	int addrlen = sizeof(clientInfo);

	char buffer[256] = "안녕";
	char buffer2[256] = { 0, };

	while (true) {
		clientSock = accept(sock, (sockaddr*)&clientInfo, &addrlen);
		//if (clientSock == INVALID_SOCKET) {
		//	return 1;
		//}

		//if(clientSock)

		//클라이언트에 대한 소켓이 반환됨 (마지막은 사이즈의 주소값을 원함 주의!)
		printf("\n%s, %d", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));
		send(clientSock, buffer, sizeof(buffer), 0);

		ret = recv(clientSock, buffer2, sizeof(buffer2), 0);

		strcat_s(buffer2, "\n");
		send(clientSock, buffer2, sizeof(buffer2), 0);


		if (ret == 0 || ret == SOCKET_ERROR) {
			printf("\n 정상종료%s, %d 나갔습니다.", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));
			break;
		} /*
		if (ret < 0) {
			printf("\n 비정상종료%s, %d 나갔습니다.", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));
			break;
		}*/
	}

	closesocket(sock);

	//윈속 종료
	WSACleanup();

	std::cout << "HELLO";
}
