#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32")

#include <Windows.h>
#define PACKET_HEADER_SIZE 4

#pragma pack(push, 1)
struct PACKET_HEADER {
	WORD len;    // ��Ŷ�� ��ü ����
	WORD type;   // ��Ŷ�� Ÿ��(����)
};

typedef struct {
	PACKET_HEADER ph;
	char msg[2048];
} UPACKET, *P_UPACKET;
#pragma pack(pop)

#define PACKET_CAHT_MSG 1000