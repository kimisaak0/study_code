#pragma once
#include <Windows.h>
#include <assert.h>
#include <tchar.h>

// 윈도우즈의 DLL (동적 연결 라이브러리)
// Kernel : 메모리를 관리하고 프로그램 실행을 담당
// GDI    : 화면 처리와 그래픽을 담당
// User   : User InterFace와 Window를 관리

//dll 파일을 추가하는 코드
#pragma comment(lib, "winmm.lib")

//다른 파일에서도 g_hWnd변수를 사용할 수 있도록 외부 변수로 등록.
extern HWND g_hWnd;

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