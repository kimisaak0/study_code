#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#pragma comment (lib, "ws2_32")

#include <Windows.h>
#define PACKET_HEADER_SIZE 4

#pragma pack(push, 1)
struct PACKET_HEADER {
	WORD len;    // 패킷의 전체 길이
	WORD type;   // 패킷의 타입(종류)
};

typedef struct {
	PACKET_HEADER ph;
	char msg[2048];
} UPACKET, *P_UPACKET;
#pragma pack(pop)

#define PACKET_CAHT_MSG 1000