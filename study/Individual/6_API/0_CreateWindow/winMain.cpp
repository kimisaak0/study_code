//1.������ ���α׷��� ����.
// - ������ API(Application Programming Interface)�� ������ ���� ���α׷����� �ʿ��� ����� ���̺귯�� �Լ� ȣ�� ���·� ����� �� �ְ� ���ش�.
// - API���� �����ϴ� ����� �ַ� ȭ�� ����, �׷��� ���, ���, ���μ��� ����, ����� ó��, ���� ���̴�.
// - �̵� ����� �̿��� ���� ���α׷��� ����ڰ� ����ϱ� ���� GUI(Graphical User Interface)�� �����ϰ� ��Ʈ��ũ�� �����ͺ��̽�(DB)�� �̿��� �� �ִ�.
// - ������ ���α׷��� ����� �Ǵ� �ü���� �������� Ư¡�� �ݿ��Ѵ�
//   1) GUI ��� ���α׷�         : ������ �����쿡 �޴�, ����, �پ��� ��Ʈ���� ǥ���� ����ڿ��� ���Ǽ��� �����Ѵ�.
//   2) �̺�Ʈ ��� ���α׷�      : ���α׷��� ���� �����ǰ� ó���� �� �ִ� �����̳� ����� �̺�Ʈ�� �Ѵ�.
//                                 �̺�Ʈ�� �ü���� �����찡 �����ϰ� ������� ������ �̺�Ʈ�� ���� �޽����� ������ ���α׷����� ������.
//                                 ������ ���α׷��� ������ �޽����� ���� �����Ѵ�.
//   3) ��Ƽ ������ ��� ���α׷� : ������� ��Ƽ ������ ������ �̿��� ������ �۾��� ���ÿ� ó���ϸ� �� �۾����� �޸�, CPU, ��ũ ���� �����Ѵ�.

//3. ������ ���α׷� ����
// - ������ ���α׷��� ũ�� WinMain(�޽��� ���ۺ�)�� WndProc(�޽��� ó����)���� ������.
//   1) WinMain������ �����츦 �����, ȭ�鿡 �����츦 ����, �����쿡�� �߻��ϰų� ���� ���α׷��� ������ �߻��ϴ� ��� �޽����� �����ϴ� ������ �Ѵ�.
//     ��Ȯ���� �޽����� �̺�Ʈ�� �߻��ϸ� ���� ��ȣ�̰�, �� ��ȣ�� ������ Ŀ���� ������. WinMain�� �̸� �ϳ��� �޾Ƽ� �޽��� ó���η� ������.
//   2) WndProc������ �޽����� �޾� �޽����� ���� ��ӵ� ������ ���δ�. 
//     �޽������� ���콺�� �������̳� ��ư Ŭ���� ���� �޽���, Ű���� ������ ���� �޽���, �پ��� ��Ʈ�ѿ��� �߻��ϴ� �޽���, �޴����� �߻��ϴ� �޽��� ���� �ִ�.

#include <Windows.h>

//�ݹ��Լ� : ���� ȣ������ �ʾƵ� ��ȣ�� ���ؼ� �ڵ�ȣ��Ǵ� �Լ�.
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

//WinMain�� 5���� ���� �����Ѵ�.
// 1) ������ Ŭ���� ���� : 
//      ������ Ŭ������ ������� �������� �Ӽ��� �����ϴ� ����ü��.
//
// 2) Ŭ������ ���� ��� : 
//      ����ü�� �Ӽ��� ������ �� �����. 
//      �� ��, �������� �����츦 ����� ���� �ִµ� ������ �����ϱ� ���� �� ������ Ŭ������ ������ �̸��� �ο������ �Ѵ�.
//
// 3) ������ ���� : 
//      ��ϵ� ������ �� �ϳ��� �����ؼ� ȭ�鿡 �����Ѵ�.
//
// 4) �߻��� �޽����� �޽��� ť�� ���� : 
//      ȭ�鿡 ��Ÿ�� �����쿡�� �̺�Ʈ�� �߻��ϸ�, �̿� ���� �޽����� Ŀ���� ���α׷��� ������. 
//      ���α׷��� �� �޽����� ������� �޽��� ť�� �����Ѵ�.
//
// 5) �޽��� ť���� �޽����� ������ WndProc() �Լ��� ������.

int WINAPI WinMain(
	HINSTANCE  hInst,         // ���α׷��� OSĿ���� �ο����ִ� �ڵ�(ID), ���α׷��� ����� �� �ο��޴´�.
	HINSTANCE  hPrevInst,     // ȣȯ���� ���ؼ��� �����ϴ� �μ�, ����� �׻� NULL�̸� ���̻� ������ �ʴ´�. 
	LPSTR      lpCmdLine,     // ��������� �Էµ� ���α׷� �μ�, ���α׷� ����� �ܺο��� �Ѿ���� ���ڿ��̴�. �ܼ� main�� argv���� ����� ��.
	int        nCmdShow       // �����찡 ȭ�鿡 ��µ� �� ���¸� �����ϴ� �μ�. Ŀ�ο��� �Ѿ�´�.  
)
{
	HWND         hwnd;          // ������ �ڵ�
	MSG          msg;           // �޽��� ����ü
	WNDCLASSEX   WndClass;      // ������ ����ü

	WndClass.cbSize = sizeof(WNDCLASSEX);                         // ����ü ũ��
	WndClass.style = CS_HREDRAW | CS_VREDRAW;                     // ��� ����
	WndClass.lpfnWndProc = WndProc;                               // �޽��� ó���� ����� �Լ� �̸�. (�߿�!) (��, ������ ������ ����ü���� ���� �ٸ� �޽��� ó�� �Լ��� ����� ���� �ִ�.)
	WndClass.cbClsExtra = 0;                                      // Ŭ���� ���� �޸�
	WndClass.cbWndExtra = 0;                                      // ������ ���� �޸�
	WndClass.hInstance = hInst;                                   // ������ �ν��Ͻ� �ڵ� ��. (�߿�!)
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // ������
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);               // Ŀ��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ����
	WndClass.lpszMenuName = NULL;                                 // �޴� �̸�
	WndClass.lpszClassName = L"MyWinodw";                         // Ŭ���� �̸� (�߿�!)
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);           // ���� ������

	//������ Ŭ���� ���
	RegisterClassEx(&WndClass);
	
	hwnd = 
		CreateWindow(
			L"MyWinodw",
			L"Windows",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInst,
			NULL
		);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(
	HWND hwnd, 
	UINT iMsg, 
	WPARAM wParam, 
	LPARAM lParam
)
{
	switch (iMsg) {
		case WM_CREATE: 
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
