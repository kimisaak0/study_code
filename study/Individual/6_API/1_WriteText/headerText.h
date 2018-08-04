#pragma once

#include "libHeader.h"
#include <tchar.h>

//1. ��� ���� ������
//  - �����쿡 �ؽ�Ʈ�� ����ϰų� �׸��� �׸����� ���� Ŀ�ο��� ��� ������ ���;� �Ѵ�.
//  - �������� ��� ������ ���� ��� �𼭸��� �������� �ϴ� ȭ�� ��ǥ�踦 ����Ѵ�.
//  - ����� ���ؼ� ���� ȭ�� ������ ����̽� ���ؽ�Ʈ(Device Context : DC)�� �Ѵ�. 
//  - ���� DC�� HDC Ÿ���� ������ �����ؼ� ����Ѵ�. 
//  - HDC Ÿ���� �޸� ������ �����ϸ�, �޸� �������� ���� ȭ�� ������ ���� �Ӽ����� ������ �� �ִ�.

//  - DC�� ������ �Լ�/ �����ϴ� �Լ� :
//
//    1) HDC BeginPaint(HWND hwnd, PAINTSTRUCT* lpPaint); / BOOL EndPaint(HWND hwnd, PAINTSTRUCT* lpPaint);
//         HWND hwnd            : DC�� �޾ƿ� �������� �ڵ鰪, 
//         PAINTSTRUCT* lpPaint : ��� ������ ���� ������ ������ PAINTSTRUCT ����ü�� �ּ�
//      : WM_PAINT �޽��� �ȿ��� ���Ǵ� ���� �Լ�. (�ٸ� �������� ��� �Ұ�)
//       GetMessage()�� �޽����� �޾ƿ��� ��κ��� ��� ������ �� ť���� �޽����� �������� WM_PAINT�޽����� ������ �ʴ´�.
//       WM_PAINT �޽����� BeginPaint()�� �׸��⸦ ������ �� �Ѵ�. 
//       �׷��Ƿ� WM_PAINT�޽��� �ȿ��� BeginPaint();�� EndPaint();�� �� �־���Ѵ�.
// 
//    2) HDC GetDC(HWND hwnd); / int ReleaseDC(HWND hwnd, HDC hdc);
//         HWND hwnd            : DC�� �޾ƿ� �������� �ڵ鰪, 
//         HDC hdc              : ��ȯ�� DC�� �ڵ鰪.
//      : �ܼ��� DC�� ������ �Լ�. �ٸ� ������ ����� �� �ִ�. 
//       BeginPaint()�� WM_PAINT �޽����� ȣ��� �� ���ǹǷ� ������ ����(��ȿȭ ����)�� ���� �׷������� GetDC�� �׷� ����� ����.

//  - �ؽ�Ʈ ��� �Լ� :
//
//    1) BOOL TextOut(HDC hdc, int x, int y, LPCTSTR lpString, int nLength);
//         HDC hdc           : �ؽ�Ʈ�� ����� ������ DC�� �ڵ鰪
//         int x, y          : �ؽ�Ʈ�� ����� ��ġ�� x,y��ǥ
//         LPCTSTR lpString  : ����� �ؽ�Ʈ
//         int nLength       : ����� �ؽ�Ʈ�� ����
//
//    2) int DrawText(HDC hdc, LPCSTR lpString, int nLength, LPRECT lpRect, UINT Flags);
//         HDC hdc           : �ؽ�Ʈ�� ����� ������ DC�� �ڵ鰪
//         LPCSTR lpString   : ����� �ؽ�Ʈ
//         int nLength       : ����� �ؽ�Ʈ�� ����
//         LPRECT lpRect     : ���ڿ��� ����� �ڽ� ������ ��ǥ�� ����� RECTŸ�� ������ �ּҰ�
//         UINT Flags        : �ڽ� ������ ��� ��ġ�� ��� ��������� ���� �÷��� ��.
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
		case WM_CREATE:      //�����츦 �� ��

			break;

		case WM_PAINT:        //�����츦 ȭ�鿡 �׸� ��
			hdc = BeginPaint(hwnd, &ps);
			TextOut(hdc, 0, 0, L"Hello World.", 10);
			DrawText(hdc, L"Hello World.", 10, &box1, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			break;

		//��ư�� ������ �Է��� ���ڰ� ��µȴ�.
		case WM_CHAR:
			hdc = GetDC(hwnd);
			str[0] = wParam;
			str[1] = '\0';
			TextOut(hdc, 100, 0, str, lstrlen(str));
			DrawText(hdc, str, lstrlen(str), &box2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			ReleaseDC(hwnd, hdc);
			break;

		case WM_DESTROY:      //�����츦 �ݾ��� ��
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}