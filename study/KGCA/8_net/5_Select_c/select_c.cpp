#include "select_c.h"

int main()
{
	SOCKET sock = Init();

	if (IPConnect(sock)) {
		std::cout << "���� ���� ���� \n";
	}

	getc(stdin); //���� ����

	while (true) {
		//�޽��� ����
		char sendBuf[256] = { 0, };
		ZeroMemory(sendBuf, sizeof(sendBuf));
		std::cout << "�Է� : "; fgets(sendBuf, 256, stdin);
		
		if (sendBuf[0] == '\n') { break; } //���͸� ġ�� �����Ű��.

		size_t iLen = strlen(sendBuf);
		if (sendBuf[iLen - 1] == '\n') {
			sendBuf[iLen - 1] = '\0';
		}
		
		int iSendByte = 0;
		iSendByte = send(sock, sendBuf, (int)iLen, 0);  //������ ���� �Լ�
		std::cout << iSendByte << "byte ����. \n";

		//�޽��� �ޱ�
		char recvBuf[256] = { 0, };
		int iRecvByte = 0;
		iRecvByte = recv(sock, recvBuf, 256, 0);        //������ ���� �Լ�
		recvBuf[iRecvByte] = '\n';
		std::cout << recvBuf << std::endl;
	}

	Release(sock);
}