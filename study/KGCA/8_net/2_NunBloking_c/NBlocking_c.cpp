#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "NBlocking_c.h"

int main()
{
	int iRet;

	WSADATA wsd;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsd);
	if ( iRet != (int)NO_ERROR) { return -1; }

	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) {	return -1; }

	std::string ip;
	std::cout << "접속할 IP를 입력하세요. \n";
	std::cin >> ip;

	SOCKADDR_IN sa_in;
	ZeroMemory(&sa_in, sizeof(sa_in));
	sa_in.sin_family = AF_INET;
	sa_in.sin_addr.s_addr = inet_addr(ip.c_str());
	sa_in.sin_port = htons(10000);

	iRet = connect(sock, (SOCKADDR*)&sa_in, sizeof(sa_in));
	if (iRet == SOCKET_ERROR) {
		if (WSAGetLastError() != WSAEWOULDBLOCK) {
			ERR_EXIT(_T("connect"));
			return -1;
		}

		//접속 시간 제한은 WSAEWOULDBLOCK일때만 세팅한다.
		if (tConnect(sock, 3000) == false) { return -1;	}
	}

	iRet = NonBlockingSocket(sock, TRUE);
	if (iRet == SOCKET_ERROR) {	return -1; }

	char buf[MAX_BUFFER_SIZE] = { 0, };
	int iEnd = 0;

	while (true) {
		if ((bool)_kbhit() == true) {
			int iValue = _getch();
			if ((int)strlen(buf) == 0 && iValue == '\r') { break; }
			if (iValue == '\r') {
				if ((int)strlen(buf) == 1) { break; } 
				iRet = send(sock, buf, (int)strlen(buf), 0);
				if (iRet == SOCKET_ERROR) {
					if (WSAGetLastError() != WSAEWOULDBLOCK) {
						ERR_EXIT(_T("send"));
						closesocket(sock);
						break;
					}
				}
				ZeroMemory(buf, sizeof(char)*MAX_BUFFER_SIZE);
				iEnd = 0;
			}
			else {
				if (iEnd < MAX_BUFFER_SIZE - 1) {
					buf[iEnd++] = iValue;
				}
			}
		}
		else {
			char bufRecv[MAX_BUFFER_SIZE] = { 0, };
			int iRecvByte = recv(sock, bufRecv, MAX_BUFFER_SIZE - 1, 0);
			if (iRecvByte == (int)NO_ERROR) { break; }
			if (iRecvByte == SOCKET_ERROR) {
				if (WSAGetLastError() != WSAEWOULDBLOCK) {
					closesocket(sock);
					ERR_EXIT(_T("recv"));
					break;
				}
				continue;
			}
			bufRecv[iRecvByte] = 0;
			printf("recv=%s\n", bufRecv);
		}
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}

