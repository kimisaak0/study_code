
#include "header.h"

int SendMsg(SOCKET sock, char* msg, WORD type) 
{
	//sock ���� ���� 
	//msg ���� �޽���
	//type ������ �޽��� Ÿ��

	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.len = strlen(msg);
	sendmsg.ph.type = type;
	memcpy(sendmsg.msg, msg, strlen(msg));
	//upacket����ü�� ä��

	int sendBytes = 0; // ���� ����Ʈ
	int iTotalSize = strlen(msg) + PACKET_HEADER_SIZE; //�������ϴ� �� ����Ʈ (�޽��� ���� + ��� ������)

	char* pMsg = (char*)&sendmsg; //upacket����ü�� �����������ͷ� ��������ȯ�ؼ� ����.

	do {
		sendBytes += send(sock, &pMsg[sendBytes], iTotalSize - sendBytes, 0);
	} while (sendBytes < iTotalSize);
	//���� ���̰� �� ���̺��� ������ ��� ����.

	return iTotalSize;
}

int RecvMsg(SOCKET sock)
{
	char buffer[256] = { 0, };
	int recvbyte = 0;

	while (true) {
		recvbyte += recv(sock, &buffer[recvbyte], sizeof(char) * PACKET_HEADER_SIZE - recvbyte, 0);
		if (recvbyte == 0) { return -1; } //���� �����Ͱ� 0�̸� ����.
		if (recvbyte == PACKET_HEADER_SIZE) { //�����ŭ ������ ��� �ؼ�
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			memcpy(&packet.ph, buffer, sizeof(char) * PACKET_HEADER_SIZE);
			//������ ������ ��Ŷ ����ü�� ��� �κп� ����.
			
			int rByte = 0;
			do {
				int iRecvByte = recv(sock, (char*)&packet.msg[rByte], sizeof(char)*packet.ph.len - rByte, 0);
				if (iRecvByte == 0) { break; }
				rByte += iRecvByte;
			} while (packet.ph.len > rByte);

			recvbyte = 0;
			switch (packet.ph.type) {
				case PACKET_CAHT_MSG: {
					printf("%s", packet.msg);
				}
			} break;

		}
	}

	return recvbyte;
}


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
	addr.sin_addr.s_addr = inet_addr("192.168.0.101");  //127.�� �������ּ�
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //127.�� �������ּ�
	addr.sin_port = htons(10000);

	//Ŭ���̾�Ʈ���� ������ ����
	int ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR) {
		return 1;
	}

	char buffer[256] = { 0, };
	char buffer2[256] = { 0, };

	while (true) {
		std::cin.getline(buffer2, 256);
		if (strcmp(buffer2, "close") == 0)
		{
			break;
		}
		SendMsg(sock, buffer2, PACKET_CAHT_MSG);

		ret = RecvMsg(sock);
		std::cout << buffer;
		
		if (ret == SOCKET_ERROR) {
			std::cout << "������ ����Ǿ����ϴ�. \n";
		}
	}

	//���� ����
	closesocket(sock);

	WSACleanup();

}