#include "packet.h"

Packet::Packet()
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_pOffset = m_uPacket.msg;
}


Packet::Packet(WORD type) 
{
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.type = type;
	m_pOffset = m_uPacket.msg;
}

void Packet::PutData(const char* pData, int iSize) {
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize);
	m_pOffset += iSize;
}

Packet& Packet::operator<<(const char* data)
{
	int iSize = strlen(data) + 1;
	PutData(data, iSize);
	return *this;
}

Packet& Packet::operator<<(int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;

}

void Packet::GetData(const char* pData, int iSize) {
	memcpy(const_cast<char*>(pData), m_pOffset, iSize);
	m_pOffset += iSize;
}

Packet& Packet::operator>>(const char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data, iSize);
	return *this;
}

Packet& Packet::operator>>(int& data)
{
	GetData((char*)&data, sizeof(int));
	return *this;

}

Packet::~Packet()
{

}