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

// 윈도우즈의 DLL (동적 연결 라이브러리)
// Kernel : 메모리를 관리하고 프로그램 실행을 담당
// GDI    : 화면 처리와 그래픽을 담당
// User   : User InterFace와 Window를 관리

//dll 파일을 추가하는 코드
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "core.lib")

//전역 변수를 외부 변수로 등록
extern HWND g_hWnd; //현재 선택된 윈도우 핸들값
extern HINSTANCE g_hInstance; //현재 프로그램 핸들값
extern HDC g_hOffScreenDC;    //현재 선택한 DC핸들값
extern double g_dSecPerFrame; //초당 프레임 수


//싱글톤 클래스 템플릿 생성.
template<class T> class singletonPattern
{
public:
	static T& GetInstance()
	{
		static T Instance;
		return Instance;
	}

};