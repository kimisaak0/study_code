//
//#include "header.h"
//
//int SendMsg(SOCKET sock, char* msg, WORD type) 
//{
//	//sock ���� ���� 
//	//msg ���� �޽���
//	//type ������ �޽��� Ÿ��
//
//	UPACKET sendmsg;
//	ZeroMemory(&sendmsg, sizeof(sendmsg));
//	sendmsg.ph.len = strlen(msg);
//	sendmsg.ph.type = type;
//	memcpy(sendmsg.msg, msg, strlen(msg));
//	//upacket����ü�� ä��
//
//	int sendBytes = 0; // ���� ����Ʈ
//	int iTotalSize = strlen(msg) + PACKET_HEADER_SIZE; //�������ϴ� �� ����Ʈ (�޽��� ���� + ��� ������)
//
//	char* pMsg = (char*)&sendmsg; //upacket����ü�� �����������ͷ� ��������ȯ�ؼ� ����.
//
//	do {
//		sendBytes += send(sock, &pMsg[sendBytes], iTotalSize - sendBytes, 0);
//	} while (sendBytes < iTotalSize);
//	//���� ���̰� �� ���̺��� ������ ��� ����.
//
//	return iTotalSize;
//}
//
//int RecvMsg(SOCKET sock)
//{
//	char buffer[256] = { 0, };
//	int recvbyte = 0;
//
//
//		recvbyte += recv(sock, &buffer[recvbyte], sizeof(char) * PACKET_HEADER_SIZE - recvbyte, 0);
//		if (recvbyte == 0) { return -1; } //���� �����Ͱ� 0�̸� ����.
//		if (recvbyte == PACKET_HEADER_SIZE) { //�����ŭ ������ ��� �ؼ�
//			UPACKET packet;
//			ZeroMemory(&packet, sizeof(packet));
//			memcpy(&packet.ph, buffer, sizeof(char) * PACKET_HEADER_SIZE);
//			//������ ������ ��Ŷ ����ü�� ��� �κп� ����.
//			
//			int rByte = 0;
//			do {
//				int iRecvByte = recv(sock, (char*)&packet.msg[rByte], sizeof(char)*packet.ph.len - rByte, 0);
//				if (iRecvByte == 0) { break; }
//				rByte += iRecvByte;
//			} while (packet.ph.len > rByte);
//
//			recvbyte = 0;
//			switch (packet.ph.type) {
//				case PACKET_CAHT_MSG: {
//					printf("%s", packet.msg);
//				}
//			} 
//
//		}
//
//
//	return recvbyte;
//}
//
//
//int main()
//{
//	WSADATA wd;
//	//���� �ʱ�ȭ
//	if (WSAStartup(MAKEWORD(2, 2), &wd) != 0) {
//		return 1;
//	}
//
//	//���� ���� (TCP�� ������)
//	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
//	if (sock == INVALID_SOCKET) { 
//		return 1; 
//	}
//
//	u_long iSockMode = TRUE; //1 Nunblocking, 0 blocking.
//
//	if (ioctlsocket(sock, FIONBIO, &iSockMode) != NO_ERROR) {
//		return 1;
//	}
//
//	SOCKADDR_IN addr;
//	ZeroMemory(&addr, sizeof(addr));
//	addr.sin_family = AF_INET;
//	addr.sin_addr.s_addr = inet_addr("192.168.0.101");  //127.�� �������ּ�
//	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //127.�� �������ּ�
//	addr.sin_port = htons(10000);
//
//	//Ŭ���̾�Ʈ���� ������ ����
//	int ret = connect(sock, (sockaddr*)&addr, sizeof(addr));
//	if (ret == SOCKET_ERROR) {
//		if (WSAGetLastError() != WSAEWOULDBLOCK) {
//			return 1;
//		}
//	}
//
//	char buffer[256] = { 0, };
//	char buffer2[256] = { 0, };
//	int iEnd = 0;
//	int iValue = 0;
//
//	while (true) {
//		if (_kbhit() == true) {
//			//std::cin.getline(buffer2, 256);
//
//			iValue = _getch();
//			if (strlen(buffer2) == 0 && iValue == '\r') { break; }
//
//			if (iValue == '\r') {
//				if (strcmp(buffer2, "close") == 0) {
//					break;
//				}
//				int iRet = SendMsg(sock, buffer2, PACKET_CAHT_MSG);
//
//				if (iRet == SOCKET_ERROR) {
//					if (WSAGetLastError() != WSAEWOULDBLOCK) {
//						closesocket(sock);
//						break;
//					}
//				}
//			}
//			else {
//				if (iEnd < 255) {
//					buffer2[iEnd++] = iValue;
//				}
//			}	
//		}
//		else {
//			ret = RecvMsg(sock);
//			if (ret == SOCKET_ERROR) {
//				if (WSAGetLastError() != WSAEWOULDBLOCK) {
//					std::cout << "������ ����Ǿ����ϴ�. \n";
//					closesocket(sock);
//					break;
//				}
//				continue;
//			}
//		}
//	}
//
//	//���� ����
//	closesocket(sock);
//
//	WSACleanup();
//
//}

#include "packet.h"

int SendMsg(SOCKET sock, const char * msg, WORD type) 
{
	Packet sendPacket(type);

	sendPacket << msg << 3000 << 10.4f;
	send(sock, (char*)&sendPacket.m_uPacket, sendPacket.m_uPacket.ph.len + PACKET_HEADER_SIZE, 0);

	char name[5] = { 0, };
	int iValue = 0;
	Packet recvPacket;
	recvPacket.m_uPacket.ph = sendPacket.m_uPacket.ph;
	memcpy(recvPacket.m_uPacket.msg, sendPacket.m_uPacket.msg, sizeof(char) * 256);
	recvPacket >> msg;
	recvPacket >> iValue;

	return 0;
}

void main()
{
	SOCKET sock = 0;
	SendMsg(sock, "game", PACKET_CAHT_MSG);
}