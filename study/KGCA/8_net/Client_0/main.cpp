
#include "header.h"

int SendMsg(SOCKET sock, char* msg, WORD type) 
{
	//sock 보낼 소켓 
	//msg 보낼 메시지
	//type 보내는 메시지 타입

	UPACKET sendmsg;
	ZeroMemory(&sendmsg, sizeof(sendmsg));
	sendmsg.ph.len = strlen(msg);
	sendmsg.ph.type = type;
	memcpy(sendmsg.msg, msg, strlen(msg));
	//upacket구조체를 채움

	int sendBytes = 0; // 보낸 바이트
	int iTotalSize = strlen(msg) + PACKET_HEADER_SIZE; //보내야하는 총 바이트 (메시지 길이 + 헤더 사이즈)

	char* pMsg = (char*)&sendmsg; //upacket구조체를 문자형포인터로 강제형변환해서 보냄.

	do {
		sendBytes += send(sock, &pMsg[sendBytes], iTotalSize - sendBytes, 0);
	} while (sendBytes < iTotalSize);
	//보낸 길이가 총 길이보다 작으면 계속 보냄.

	return iTotalSize;
}

int RecvMsg(SOCKET sock)
{
	char buffer[256] = { 0, };
	int recvbyte = 0;

	while (true) {
		recvbyte += recv(sock, &buffer[recvbyte], sizeof(char) * PACKET_HEADER_SIZE - recvbyte, 0);
		if (recvbyte == 0) { return -1; } //받은 데이터가 0이면 종료.
		if (recvbyte == PACKET_HEADER_SIZE) { //헤더만큼 받으면 헤더 해석
			UPACKET packet;
			ZeroMemory(&packet, sizeof(packet));
			memcpy(&packet.ph, buffer, sizeof(char) * PACKET_HEADER_SIZE);
			//버퍼의 내용을 패킷 구조체의 헤더 부분에 복사.
			
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
	addr.sin_addr.s_addr = inet_addr("192.168.0.101");  //127.은 루프백주소
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //127.은 루프백주소
	addr.sin_port = htons(10000);

	//클라이언트에서 서버에 접속
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
			std::cout << "서버가 종료되었습니다. \n";
		}
	}

	//윈속 종료
	closesocket(sock);

	WSACleanup();

}