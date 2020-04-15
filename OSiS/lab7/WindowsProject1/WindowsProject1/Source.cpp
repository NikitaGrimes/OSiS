//#include <Windows.h>
////#include "stdafx.h"
//#include "WindowsProject1.h"
//
//#define MAX_LOADSTRING 100
//
//// ���������� ����������:
//HINSTANCE hInst;                                // ������� ���������
//WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
//WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
//
//bool DrawingMode = false;
//bool MoveMode = false;
//bool RMode = false;
//int xLocation = 0, yLocation = 0, objectNumber = 15, currentIndex = 0;
//void Draw(HDC, int, int);
//int* XLocationsArray;
//int* YLocationsArray;
//
//HWND hWndListL;
//HWND hWndListR;
//HWND hWndButton;
//
//// ��������� ���������� �������, ���������� � ���� ������ ����:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//	_In_opt_ HINSTANCE hPrevInstance,
//	_In_ LPWSTR    lpCmdLine,
//	_In_ int       nCmdShow)
//{
//	UNREFERENCED_PARAMETER(hPrevInstance);
//	UNREFERENCED_PARAMETER(lpCmdLine);
//
//	// TODO: ���������� ��� �����.
//	XLocationsArray = new int[objectNumber];
//	YLocationsArray = new int[objectNumber];
//	// ������������� ���������� �����
//	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
//	MyRegisterClass(hInstance);
//
//	// ��������� ������������� ����������:
//	if (!InitInstance(hInstance, nCmdShow))
//	{
//		return FALSE;
//	}
//
//	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
//
//	MSG msg;
//
//	// ���� ��������� ���������:
//	while (GetMessage(&msg, nullptr, 0, 0))
//	{
//		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//	}
//
//	return (int)msg.wParam;
//}
//
//
//
////
////  �������: MyRegisterClass()
////
////  ����: ������������ ����� ����.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEXW wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style = CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc = WndProc;
//	wcex.cbClsExtra = 0;
//	wcex.cbWndExtra = 0;
//	wcex.hInstance = hInstance;
//	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
//	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
//	wcex.lpszClassName = szWindowClass;
//	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassExW(&wcex);
//}
//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	MSG Msg;
//	HWND hWnd;
//	hInst = hInstance;
//
//
//
//	//Register Window Class
//	//RegisterClassEx(&WndClsEx);
//
//
//	//Create Window
//	//hWnd = CreateWindowEx(NULL, "My Window", "Windows Application", WS_OVERLAPPEDWINDOW, 200, 200, 640, 480, NULL, NULL, hInstance, NULL);
//	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//	if (!hWnd)
//	{
//		return FALSE;
//	}
//
//
//	SendMessage(hWndListL, LB_ADDSTRING, NULL, (LPARAM)"one");
//	SendMessage(hWndListL, LB_ADDSTRING, NULL, (LPARAM)"two");
//
//
//
//	//Show Window
//	ShowWindow(hWnd, SW_SHOWNORMAL);
//
//
//	while (GetMessage(&Msg, NULL, 0, 0))
//	{
//		TranslateMessage(&Msg);
//		DispatchMessage(&Msg);
//	}
//
//
//	return 0;
//}
//
//
//
//LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
//{
//	char buffer[50] = "";
//
//
//	switch (Msg)
//	{
//	case WM_CREATE:
//		//Create Listbox's
//		hWndListL = CreateWindowEx(NULL, L"LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY, 50, 35, 200, 100, hWnd, NULL, GetModuleHandle(NULL), NULL);
//		hWndListR = CreateWindowEx(NULL, L"LISTBOX", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY, 350, 35, 200, 100, hWnd, NULL, GetModuleHandle(NULL), NULL);
//
//		//Create Button
//		hWndButton = CreateWindowEx(NULL, L"BUTTON", L"START", WS_CHILD | WS_VISIBLE, 200, 0, 200, 25, hWnd, HMENU(56), hInst, NULL);//CreateWindowEx(NULL, "BUTTON", "OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_DISABLED, 50, 220, 100, 24, hWnd, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);
//
//		break;
//	case WM_COMMAND:
//		switch (HIWORD(wParam))
//		{
//		case LBN_SELCHANGE:
//		{
//			//EnableWindow( GetDlgItem( hWnd, (HMENU)IDC_BUTTON_MAIN ), TRUE );
//			EnableWindow(hWndButton, true);
//			break;
//		}
//		}
//		switch (LOWORD(wParam))
//		{
//		case 56:
//		{
//			//length = SendMessage(hWndListL, LB_GETTEXTLEN, NULL, NULL);
//			SendMessage(hWndListL, LB_GETTEXT, NULL, (LPARAM)buffer);
//			SendMessage(hWndListR, LB_ADDSTRING, NULL, (LPARAM)buffer);
//			SendMessage(hWndListL, LB_DELETESTRING, NULL, NULL);
//			EnableWindow(hWndButton, false);
//			break;
//		}
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(WM_QUIT);
//		break;
//	}
//
//	return DefWindowProc(hWnd, Msg, wParam, lParam);
//}