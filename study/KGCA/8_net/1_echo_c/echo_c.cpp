#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	int ret = 0;

	WSADATA WSD;
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);        //������ ���� �ʱ�ȭ
	if (ret != 0) { return -1; }

	
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);        //���� ����	
	if (sock == INVALID_SOCKET) { return -1; }

	

	do {
		if (ret == SOCKET_ERROR) {
			std::cout << "IP�� �߸� �Է��ϼ̰ų�, ������ �����ֽ��ϴ�.\n";
		}

		std::string ip;
		std::cout << "������ IP�� �Է��ϼ���. \n";
		std::cin >> ip;

		SOCKADDR_IN addrIn; 
		ZeroMemory(&addrIn, sizeof(addrIn));                        //htons : host to network short, ntohs : netword to host short     
		addrIn.sin_family = AF_INET;						        //host : Little Endian ���(���������� �����), network : Big Endian ��� 
		addrIn.sin_addr.s_addr = inet_addr(ip.c_str());		        //������ IP�ּҸ� ������ �ʿ� ���� ��� IP(INADDR_ANY)�� ������ �ȴ�.					
		addrIn.sin_port = htons(10000);                             //���ÿ� ���α׷��� ��Ʈ��ȣ�� 10000���� ����.   
	
		ret = connect(sock, (sockaddr*)&addrIn, sizeof(addrIn));    //�Է��� IP�� ���ӽõ�.
	} while (ret == SOCKET_ERROR);

	


	

	getc(stdin);

	std::cout << "���� ���� ���� \n";

	while (true) {
		//�޽��� ����
		char sendBuf[256] = { 0, };
		std::cout << "�Է� : "; fgets(sendBuf, 256, stdin);
		if (sendBuf[0] == '\n') { break; } //���͸� ġ�� �����Ű��.

		size_t iLen = 0;
		iLen = strlen(sendBuf) - 1;

		int iSendByte = 0;
		iSendByte = send(sock, sendBuf, (int)iLen, 0);  //������ ���� �Լ�
		std::cout << iSendByte << "byte ����. \n";

		//�޽��� �ޱ�
		char recvBuf[256] = { 0, };
		int iRecvByte = 0;
		iRecvByte = recv(sock, recvBuf, 256, 0);
		if (iRecvByte == 0 || iRecvByte == SOCKET_ERROR) {
			std::cout << "���� ����";
		}
		recvBuf[iRecvByte] = '\n';

		std::cout << recvBuf << std::endl;
	}

	//
	closesocket(sock);

	//
	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "Ŭ���� ����";
		return -1;
	}
	else {
		return 0;
	}

}