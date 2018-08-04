#pragma once

#include "libHeader.h"
#include <tchar.h>

//1. 출력 영역 얻어오기
//  - 윈도우에 텍스트를 출력하거나 그림을 그리려면 먼저 커널에서 출력 영역을 얻어와야 한다.
//  - 윈도우의 출력 영역은 좌측 상단 모서리를 원점으로 하는 화면 좌표계를 사용한다.
//  - 출력을 위해서 얻어온 화면 영역을 디바이스 컨텍스트(Device Context : DC)라 한다. 
//  - 얻어온 DC는 HDC 타입의 변수에 저장해서 사용한다. 
//  - HDC 타입은 메모리 영역을 관리하며, 메모리 영역에는 얻어온 화면 영역에 대한 속성값을 저장할 수 있다.

//  - DC를 얻어오는 함수/ 해제하는 함수 :
//
//    1) HDC BeginPaint(HWND hwnd, PAINTSTRUCT* lpPaint); / BOOL EndPaint(HWND hwnd, PAINTSTRUCT* lpPaint);
//         HWND hwnd            : DC를 받아올 윈도우의 핸들값, 
//         PAINTSTRUCT* lpPaint : 출력 영역에 대한 정보를 저장할 PAINTSTRUCT 구조체의 주소
//      : WM_PAINT 메시지 안에서 사용되는 전용 함수. (다른 곳에서는 사용 불가)
//       GetMessage()로 메시지를 받아오면 대부분의 경우 가져온 뒤 큐에서 메시지를 지우지만 WM_PAINT메시지는 지우지 않는다.
//       WM_PAINT 메시지는 BeginPaint()가 그리기를 시작할 때 한다. 
//       그러므로 WM_PAINT메시지 안에는 BeginPaint();와 EndPaint();가 꼭 있어야한다.
// 
//    2) HDC GetDC(HWND hwnd); / int ReleaseDC(HWND hwnd, HDC hdc);
//         HWND hwnd            : DC를 받아올 윈도우의 핸들값, 
//         HDC hdc              : 반환할 DC의 핸들값.
//      : 단순히 DC만 얻어오는 함수. 다른 곳에서 사용할 수 있다. 
//       BeginPaint()는 WM_PAINT 메시지가 호출될 때 사용되므로 지워진 영역(무효화 영역)을 새로 그려주지만 GetDC는 그런 기능이 없다.

//  - 텍스트 출력 함수 :
//
//    1) BOOL TextOut(HDC hdc, int x, int y, LPCTSTR lpString, int nLength);
//         HDC hdc           : 텍스트를 출력할 윈도우 DC의 핸들값
//         int x, y          : 텍스트를 출력할 위치의 x,y좌표
//         LPCTSTR lpString  : 출력할 텍스트
//         int nLength       : 출력할 텍스트의 길이
//
//    2) int DrawText(HDC hdc, LPCSTR lpString, int nLength, LPRECT lpRect, UINT Flags);
//         HDC hdc           : 텍스트를 출력할 윈도우 DC의 핸들값
//         LPCSTR lpString   : 출력할 텍스트
//         int nLength       : 출력할 텍스트의 길이
//         LPRECT lpRect     : 문자열을 출력할 박스 영역의 좌표가 저장된 RECT타입 변수의 주소값
//         UINT Flags        : 박스 영역의 어느 위치에 어떻게 출력할지에 대한 플래그 값.
//


WNDPROC(WndProc)
{
	HDC          hdc;
	PAINTSTRUCT	 ps;
	
	RECT         box1;
	box1.left = 50;
	box1.top = 40;
	box1.right = 200;
	box1.bottom = 120;

	RECT         box2;
	box2.left = 210;
	box2.top = 130;
	box2.right = 360;
	box2.bottom = 210;

	static TCHAR str[2];

	switch (iMsg) {
		case WM_CREATE:      //윈도우를 열 때

			break;

		case WM_PAINT:        //윈도우를 화면에 그릴 때
			hdc = BeginPaint(hwnd, &ps);
			TextOut(hdc, 0, 0, L"Hello World.", 10);
			DrawText(hdc, L"Hello World.", 10, &box1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			break;

		//버튼을 누르면 입력한 문자가 출력된다.
		case WM_CHAR:
			hdc = GetDC(hwnd);
			str[0] = wParam;
			str[1] = '\0';
			TextOut(hdc, 100, 0, str, lstrlen(str));
			DrawText(hdc, str, lstrlen(str), &box2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ReleaseDC(hwnd, hdc);
			break;

		case WM_DESTROY:      //윈도우를 닫았을 때
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}