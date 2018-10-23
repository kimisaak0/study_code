#define _CRT_SECURE_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
//#include <ws2tcpip.h>

#include <iostream>
#include <string>
#include <tchar.h>
#include <conio.h>

#define MAX_BUFFER_SIZE 256

//오류 처리를 위한 함수
static void ERR_EXIT(const TCHAR* msg)
{
	setlocale(LC_ALL, "KOREAN"); // 지역 설정.

	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(TCHAR*)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (TCHAR*)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}

//static void ERR_print(const TCHAR* msg)
//{
//	setlocale(LC_ALL, "KOREAN"); // 지역 설정.
//
//	LPVOID lpMsgBuf;
//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
//		NULL, WSAGetLastError(),
//		GetLocaleInfoEx(LOCALE_NAME_SYSTEM_DEFAULT, LOCALE_RETURN_NUMBER, 0, 0),
//		(TCHAR*)&lpMsgBuf, 0, NULL);
//	printf("[%s] %s", (char*)msg, (char*)lpMsgBuf);
//	LocalFree(lpMsgBuf);
//}

static int NonBlockingSocket(SOCKET sock, u_long uMode)
{
	//To make NonBlocking Socket, controls the I/O mode of a socket
	int iRet = ioctlsocket(sock, FIONBIO, &uMode);
	if (iRet != NO_ERROR) {
		ERR_EXIT(_T("논블록킹 소켓으로 변환 실패"));
	}
	return iRet;
}

static bool tConnect(SOCKET sock, int out_time)
{
	int iRet;
	u_long uMode;

	TIMEVAL TimeOut;
	TimeOut.tv_sec = out_time;
	TimeOut.tv_usec = 0;
	
	uMode = 1;
	iRet = ioctlsocket(sock, FIONBIO, &uMode);
	if (iRet != NO_ERROR) {
		std::cout << "ioctlsocket failed with error : " << iRet << std::endl;
	}

	//논블로킹 소켓으로 다시 전환한다.
	uMode = 0;
	iRet = ioctlsocket(sock, FIONBIO, &uMode);
	if (iRet != NO_ERROR) {
		std::cout << "ioctlsocket failed with error : " << iRet << std::endl;
	}

	fd_set Write, Err;
	FD_ZERO(&Write);
	FD_ZERO(&Err);
	FD_SET(sock, &Write);
	FD_SET(sock, &Err);

	//논블로킹 소켓으로 타임아웃만큼 대기한다.
	iRet = select(0, NULL, &Write, &Err, &TimeOut);
	if (iRet == 0) {
		return true; //타임아웃
	}
	if (FD_ISSET(sock, &Write)) {
		return true; //connected!
	}
//	if (FD_ISSET(sock, &Err)) 
		return false; //Error
}

