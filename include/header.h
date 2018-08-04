#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <map>
#include <list>

typedef std::basic_string<char> C_STR;
typedef std::basic_string<wchar_t> W_STR;
typedef std::basic_string<TCHAR> T_STR;

// ���������� DLL (���� ���� ���̺귯��)
// Kernel : �޸𸮸� �����ϰ� ���α׷� ������ ���
// GDI    : ȭ�� ó���� �׷����� ���
// User   : User InterFace�� Window�� ����

//dll ������ �߰��ϴ� �ڵ�
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "core.lib")

//���� ������ �ܺ� ������ ���
extern HWND g_hWnd; //���� ���õ� ������ �ڵ鰪
extern HINSTANCE g_hInstance; //���� ���α׷� �ڵ鰪
extern HDC g_hOffScreenDC;    //���� ������ DC�ڵ鰪
extern double g_dSecPerFrame; //�ʴ� ������ ��


//�̱��� Ŭ���� ���ø� ����.
template<class T> class singletonPattern
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}

};