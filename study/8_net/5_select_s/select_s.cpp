#include "select_s.h"

int main()
{
	SOCKET sock = Init();

	NonBlockingSocket(sock, TRUE);

	FD_SET g_rset, g_wset;

	while (true) {
		int iRet = 0;
		SOCKET client;
		SOCKADDR_IN addr;
		ZeroMemory(&addr, sizeof(addr));
		int addrlen = sizeof(addr);

		//���� �� �ʱ�ȭ
		FD_ZERO(&g_rset);
		FD_ZERO(&g_wset);
		FD_SET(sock, &g_rset);

		for (int i = 0; i < g_iTotalSockets; i++) {
			if (SIArr[i]->iRecvByte > SIArr[i]->iSendByte) {
				FD_SET(SIArr[i]->sock, &g_wset);
			}
			else {
				FD_SET(SIArr[i]->sock, &g_rset);
			}
		}

		//select()
		iRet = select(0, &g_rset, &g_wset, NULL, NULL);
		if (iRet == SOCKET_ERROR) { ERR_EXIT(_T("select()")); }

		//���ϼ� �˻�(1) : ���� ����
		if (FD_ISSET(sock, &g_rset)) {
			client = ClientAccept(sock);
			if (client == INVALID_SOCKET) {
				ERR_EXIT(_T("accept()"));
			}
			else {
				_tprintf(_T("���� [%s]"), inet_ntoa(addr.sin_addr));
				AddSI(client);
			}
		}

		//���ϼ� �˻�(2) : ������ ���
		for (int i = 0; i < g_iTotalSockets; i++) {
			if (FD_ISSET(SIArr[i]->sock, &g_rset)) {
				//������ �ޱ�
				iRet = recv(SIArr[i]->sock, SIArr[i]->buf, 256, 0);
				if (iRet == SOCKET_ERROR) {
					RemoveSI(i);
					continue;
				}
				SIArr[i]->iRecvByte = iRet;

				SIArr[i]->buf[iRet] = '\0';
				printf("%s\n", SIArr[i]->buf);
			}

			//������ ������
			if (FD_ISSET(SIArr[i]->sock, &g_wset)) {
				iRet = send(SIArr[i]->sock, SIArr[i]->buf, SIArr[i]->iRecvByte - SIArr[i]->iSendByte, 0);
				if (iRet == SOCKET_ERROR) {
					RemoveSI(i);
					continue;
				}
				SIArr[i]->iSendByte += iRet;
				if (SIArr[i]->iRecvByte == SIArr[i]->iSendByte) {
					SIArr[i]->iRecvByte = SIArr[i]->iSendByte = 0;
				}
			}
		}
	}

	Release(sock);
}