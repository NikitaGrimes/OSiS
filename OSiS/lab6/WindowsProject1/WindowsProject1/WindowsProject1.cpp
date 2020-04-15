#include "stdafx.h"
#include "WindowsProject1.h"
#define MAX_LOADSTRING 100
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
bool DrawingMode = true;
bool MoveMode = false;
bool RMode = false;
int xLocation = 550, yLocation = 250, objectNumber = 15, currentIndex = 0;
void Draw(HDC, int, int);
int *XLocationsArray;
int *YLocationsArray;
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	XLocationsArray = new int[objectNumber];
	YLocationsArray = new int[objectNumber];
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; 
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	HWND hWnd1 = CreateWindowEx(NULL, L"BUTTON", L"START", WS_CHILD | WS_VISIBLE, 200, 0, 200, 25, hWnd, HMENU(56), hInst, NULL);
	HWND hWnd2 = CreateWindowEx(NULL, L"BUTTON", L"STOP", WS_CHILD | WS_VISIBLE, 400, 0, 200, 25, hWnd, HMENU(58), hInst, NULL);
	HWND hWnd3 = CreateWindowEx(NULL, L"BUTTON", L"EXIT", WS_CHILD | WS_VISIBLE, 800, 0, 200, 25, hWnd, HMENU(57), hInst, NULL);
	if (!hWnd)
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


void UpdateGraph(HWND hwnd, HDC dc, int xLocation, int yLocation)
{
	if (DrawingMode)
	{
		XLocationsArray[currentIndex] = xLocation;
		YLocationsArray[currentIndex] = yLocation;
		currentIndex++;
		if (currentIndex == objectNumber)
		{
			objectNumber += 15;
			XLocationsArray = (int*)realloc(XLocationsArray, objectNumber * sizeof(int));
			YLocationsArray = (int*)realloc(YLocationsArray, objectNumber * sizeof(int));
		}
	}
	for (int i = 0; i < currentIndex; i++)
	{
		LPCWSTR message = L"Идущая надпись";
		RECT rc;
		rc.left = (XLocationsArray[i] - 75);
		rc.top = (YLocationsArray[i] + 20);
		rc.right = XLocationsArray[i] + 75;
		rc.bottom = YLocationsArray[i] - 5;
		DrawText(dc, message, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);
		break;
	}
	case WM_TIMER:
	{
		if (wParam == 1)
		{
			if (RMode)
				XLocationsArray[currentIndex - 1] += 5;
			else XLocationsArray[currentIndex - 1] -= 5;
			if (XLocationsArray[currentIndex - 1] > 930 || XLocationsArray[currentIndex - 1] < 30)
				KillTimer(hWnd, 1);
			DrawingMode = false;
			InvalidateRect(hWnd, NULL, true);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		DrawingMode = true;
		xLocation = LOWORD(lParam);
		yLocation = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, true);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case 55:
		{
			KillTimer(hWnd, 1);
			MoveMode = false;
			DrawingMode = false;
			currentIndex = 0;
			delete(XLocationsArray);
			delete(YLocationsArray);
			XLocationsArray = new int[objectNumber];
			YLocationsArray = new int[objectNumber];
			InvalidateRect(hWnd, NULL, true);
			break;
		}
		case 56:
		{
			if (!MoveMode)
			{
				if (XLocationsArray[currentIndex - 1] <= 500)
					RMode = true;
				else RMode = false;
				SetTimer(hWnd, 1, 50, NULL);
				MoveMode = true;
			}
			break;
		}
		case 57:
		{
			DestroyWindow(hWnd);
			break;
		}
		case 58:
		{
			if (MoveMode)
			{
				KillTimer(hWnd, 1);
				MoveMode = false;
			}
			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Draw(hdc, xLocation, yLocation);
		UpdateGraph(hWnd, hdc, xLocation, yLocation);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 1);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Draw(HDC hdc, int xLocation, int yLocation)
{
	HPEN holdPen, hGreenPen;
	hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	holdPen = (HPEN)SelectObject(hdc, hGreenPen);
	HBRUSH holdBrush, hSkyBrush;
	hSkyBrush = CreateSolidBrush(RGB(0, 204, 255));
	holdBrush = (HBRUSH)SelectObject(hdc, hSkyBrush);
	if (DrawingMode)
	{
		XLocationsArray[currentIndex] = xLocation;
		YLocationsArray[currentIndex] = yLocation;
		currentIndex++;
		if (currentIndex == objectNumber)
		{
			objectNumber += 15;
			XLocationsArray = (int*)realloc(XLocationsArray, objectNumber * sizeof(int));
			YLocationsArray = (int*)realloc(YLocationsArray, objectNumber * sizeof(int));
		}
	}
	for (int i = 0; i < currentIndex; i++)
	{
		MoveToEx(hdc, XLocationsArray[i] - 30, YLocationsArray[i], NULL);
	}
	DrawingMode = false;
	SelectObject(hdc, holdPen);
	DeleteObject(hGreenPen);
}