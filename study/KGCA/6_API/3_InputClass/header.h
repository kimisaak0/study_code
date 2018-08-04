#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

// ���������� DLL (���� ���� ���̺귯��)
// Kernel : �޸𸮸� �����ϰ� ���α׷� ������ ���
// GDI    : ȭ�� ó���� �׷����� ���
// User   : User InterFace�� Window�� ����

//dll ������ �߰��ϴ� �ڵ�
#pragma comment(lib, "winmm.lib")

//�ٸ� ���Ͽ����� g_hWnd������ ����� �� �ֵ��� �ܺ� ������ ���.
extern HWND g_hWnd;

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