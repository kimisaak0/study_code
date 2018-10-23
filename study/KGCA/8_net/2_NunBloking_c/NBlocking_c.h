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

//소켓을 넌블로킹 소켓으로 변환한다.
static int NonBlockingSocket(SOCKET sock, u_long uMode)
{	
	int iRet = ioctlsocket(sock, FIONBIO, &uMode);
	if (iRet != NO_ERROR) {
		ERR_EXIT(_T("논블록킹 소켓으로 변환 실패"));
	}
	return iRet;
}

//static bool tConnect(SOCKET sock, int out_time)
//{
//	int iRet;
//
//	TIMEVAL TimeOut;
//	TimeOut.tv_sec = out_time;
//	TimeOut.tv_usec = 0;
//	
//	NonBlockingSocket(sock, TRUE);
//
//	//블로킹 소켓으로 다시 전환한다.
//	NonBlockingSocket(sock, FALSE);
//
//	fd_set Write, Err;
//	FD_ZERO(&Write);
//	FD_ZERO(&Err);
//	FD_SET(sock, &Write);
//	FD_SET(sock, &Err);
//
//	//블로킹 소켓으로 타임아웃만큼 대기한다.
//	iRet = select(0, NULL, &Write, &Err, &TimeOut);
//	if (iRet == 0) {
//		return true; //타임아웃
//	}
//	if (FD_ISSET(sock, &Write)) {
//		return true; //connected!
//	}
////	if (FD_ISSET(sock, &Err)) 
//		return false; //Error
//}

