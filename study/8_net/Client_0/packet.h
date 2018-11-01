#pragma once
#include "header.h"



class Packet
{
public:
	UPACKET m_uPacket;
	char* m_pOffset;

public:
	Packet& operator<< (const char* data);
	Packet& operator<< (int data);
	void PutData(const char* pData, int iSize);

	Packet& operator>> (const char* data);
	Packet& operator>> (int& data);
	void GetData(const char* pData, int iSize);

public:
	Packet();
	Packet(WORD type);

	virtual ~Packet();
};