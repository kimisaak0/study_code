#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

//���� ����
//������   : TCP(SOCK_STREAM, IPPROTO_TCP)
//�񿬰��� : UDP(SOCK_DGRAM,  IPPROTO_UDP) 


int main()
{
	int ret;

	WSADATA WSD;
	ret = WSAStartup(MAKEWORD(2, 2), &WSD);        //������ ���� �ʱ�ȭ
	if (ret != 0) { return -1; }
	
	SOCKET sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);        //���� ����	
	if (sock == INVALID_SOCKET) { return -1; }

	//��� ���� ����
	SOCKADDR_IN addrIn;
	ZeroMemory(&addrIn, sizeof(addrIn));           //htons : host to network short, ntohs : netword to host short    
	addrIn.sin_family = AF_INET;                   //host : Little Endian ���(���������� �����), network : Big Endian ��� 
	addrIn.sin_addr.s_addr = htonl(INADDR_ANY);    //������ IP�ּҸ� ������ �ʿ� ���� ��� IP(INADDR_ANY)�� ������ �ȴ�.
	addrIn.sin_port = htons(10000);                //���ÿ� ���α׷��� ��Ʈ��ȣ�� 10000���� ����.  
												   	
	ret = bind(sock, (SOCKADDR*)&addrIn, sizeof(addrIn));    // ���Ͽ� ��� ���� ���ε�
	if (ret == SOCKET_ERROR) { return -1; }					 

	ret = listen(sock, SOMAXCONN);                           // ������ ��� ���·� ����.
	if (ret == SOCKET_ERROR) { return -1; }
	
	while (true) {
		SOCKADDR_IN clientAddr;
		int addrlen = sizeof(clientAddr);

		SOCKET client = 0;
		client = accept(sock, (SOCKADDR*)&clientAddr, &addrlen);  //Ŭ���̾�Ʈ ������ ���ο� ������ ���� ����. (����ó��)
		if (client == INVALID_SOCKET) {
			printf("Ŭ���̾�Ʈ ���� ����");
			continue; 
		}
		printf("Ŭ���̾�Ʈ ���� [ip:%s]\n", inet_ntoa(clientAddr.sin_addr));


		//���� �ý���
		while (true) {
			char recvBuf[256] = { 0, };
			ZeroMemory(recvBuf, sizeof(recvBuf));
			int iRecvByte = 0;
			iRecvByte = recv(client, recvBuf, 256, 0);   //�����͸� �޴´�. ������ SOCKET_ERROR, �����̸� ���� ������ũ�⸦ ��ȯ�Ѵ�.
			if (iRecvByte == 0)  {
				printf("Ŭ���̾�Ʈ ���� ���� [ip:%s]", inet_ntoa(clientAddr.sin_addr));
				break;
			}
			else if (iRecvByte == SOCKET_ERROR) {
				printf("Ŭ���̾�Ʈ ������ ���� [ip:%s]", inet_ntoa(clientAddr.sin_addr));
				break;
			}
			recvBuf[iRecvByte] = '\n';
			printf("%s", recvBuf);

			int iSendByte = 0;
			iSendByte = send(client, recvBuf, iRecvByte, 0);  //�����͸� ������. 
			if (iSendByte == SOCKET_ERROR) {
				printf("send ����");
				continue;
			}
		}
		//Ŭ���̾�Ʈ ����
		closesocket(client);
	}

	closesocket(sock);
	//������ ���� �Ҹ�
	ret = WSACleanup();
	if (ret == SOCKET_ERROR) {
		std::cout << "Ŭ���� ����";
		return -1;
	}
	else {
		return ret;
	}

}