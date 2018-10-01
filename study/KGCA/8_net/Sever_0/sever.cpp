#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32")

#include <vector>

std::vector<SOCKET> clientList;
//����

int main()
{
	WSADATA wd;
	//���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
		return 1;
	}

	//���� ���� (TCP�� ������)
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		return 1;
	}

	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = inet_addr("192.168.0.104");
	addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
	addr.sin_port = htons(10000);
	//ȣ��Ʈ ����(��Ʋ�����)���� ��Ʈ��ũ ����(�򿣵��).

	//������ Ŭ���̾�Ʈ ����
	int ret = bind(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	//�̺�Ʈ ó�� ��û
	ret = listen(sock, SOMAXCONN);
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	SOCKET clientSock;
	SOCKADDR_IN clientInfo;
	int addrlen = sizeof(clientInfo);

	char buffer[256] = "�ȳ�";
	char buffer2[256] = { 0, };

	while (true) {
		//Ŭ���̾�Ʈ�� ���� ������ ��ȯ�� (�������� �������� �ּҰ��� ���� ����!)
		clientSock = accept(sock, (sockaddr*)&clientInfo, &addrlen);
		if (clientSock == INVALID_SOCKET) {
			break;
		}

		printf("\n%s, %d", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));

		send(clientSock, buffer, sizeof(buffer), 0);


		while (true) {
			ret = recv(clientSock, buffer2, sizeof(buffer2), 0);

			clientList.push_back(clientSock);

			for (int iUser = 0; iUser < clientList.size(); iUser++) {
				send(clientList[iUser], buffer2, sizeof(buffer2), 0);
			}
		}

		if (ret == 0) {
			printf("\n ��������%s, %d �������ϴ�.", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));
		}

		if (ret < 0) {
			printf("\n ����������%s, %d �������ϴ�.", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));
		}

	}

	closesocket(sock);

	//���� ����
	WSACleanup();

	std::cout << "HELLO";
}