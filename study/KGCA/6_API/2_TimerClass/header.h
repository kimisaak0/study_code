#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

// ���������� DLL (���� ���� ���̺귯��)
// Kernel : �޸𸮸� �����ϰ� ���α׷� ������ ���
// GDI    : ȭ�� ó���� �׷����� ���
// User   : User InterFace�� Window�� ����

#pragma comment(lib, "winmm.lib")

extern HWND g_hWnd;


