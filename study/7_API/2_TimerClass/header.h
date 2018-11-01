#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

// 윈도우즈의 DLL (동적 연결 라이브러리)
// Kernel : 메모리를 관리하고 프로그램 실행을 담당
// GDI    : 화면 처리와 그래픽을 담당
// User   : User InterFace와 Window를 관리

#pragma comment(lib, "winmm.lib")

extern HWND g_hWnd;


