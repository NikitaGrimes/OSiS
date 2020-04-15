#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100
#define LANG_ENGLISH
HINSTANCE hInst;     
WCHAR szTitle[MAX_LOADSTRING]; 
WCHAR szWindowClass[MAX_LOADSTRING]; 
HWND hEdit;
HWND hListBox1;
HWND hListBox2;
CHAR str_1[] = { "str 1" };
CHAR str_2[] = { "str 2" };
TCHAR buff[1024];

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
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow))
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
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
   HWND hButtonAdd = CreateWindowEx(NULL, L"BUTTON", L"ADD", WS_CHILD | WS_VISIBLE, 200, 300, 200, 50, hWnd, HMENU(56), hInst, NULL);
   HWND hButtonClear = CreateWindowEx(NULL, L"BUTTON", L"CLEAR", WS_CHILD | WS_VISIBLE, 400, 300, 200, 50, hWnd, HMENU(57), hInst, NULL);
   HWND hButtonRight = CreateWindowEx(NULL, L"BUTTON", L"TO_RIGHT", WS_CHILD | WS_VISIBLE, 600, 300, 200, 50, hWnd, HMENU(58), hInst, NULL);
   HWND hButtonDelate = CreateWindowEx(NULL, L"BUTTON", L"DELATE", WS_CHILD | WS_VISIBLE, 800, 300, 200, 50, hWnd, HMENU(59), hInst, NULL);
   LPCWSTR message = L"My First Window";
   hListBox1 = CreateWindowEx(NULL, L"listbox", L"box",
	   WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY,
	   300, 100, 200, 100,
	   hWnd, HMENU(60), hInst, NULL);
   hListBox2 = CreateWindowEx(NULL, L"listbox", L"box",
	   WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY,
	   700, 100, 200, 100,
	   hWnd, HMENU(60), hInst, NULL);
   hEdit = CreateWindowEx(NULL, L"EDIT", L"SMTH", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | LBS_NOTIFY, 350, 50, 500, 30, hWnd, HMENU(60), hInst, NULL);
   InvalidateRect(hListBox1, NULL, TRUE);
   if (!hWnd)
   {
      return FALSE;
   }
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		return 0;
	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
			case 56:
			{
				GetWindowText(hEdit, buff, 1024);
				bool noSuchString = true;       
				if (SendMessage(hListBox1, LB_GETCOUNT, NULL, NULL) == 0)
					SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)buff);
				else
				{
					for(int i = 0; i < SendMessage(hListBox1, LB_GETCOUNT, NULL, NULL); i++) 
                    {
						if (SendMessage(hListBox1, LB_FINDSTRINGEXACT, i, (LPARAM)buff) != LB_ERR)
							noSuchString = false;
					}
					if(noSuchString)
						SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)buff);
				}
				break;
			}
			case 57:
			{
				int LB1Strings = SendMessage(hListBox1, LB_GETCOUNT, NULL, NULL), LB2Strings = SendMessage(hListBox2, LB_GETCOUNT, NULL, NULL);
				for (int i = 0; i < LB1Strings; i++)
					SendMessage(hListBox1, LB_DELETESTRING, 0, 0);
				for (int i = 0; i < LB2Strings; i++)
					SendMessage(hListBox2, LB_DELETESTRING, 0, 0);
			}
			break;
			case 58:
			{
				int LB1Strings = SendMessage(hListBox1, LB_GETCARETINDEX, NULL, NULL);
				SendMessage(hListBox1, LB_GETTEXT, LB1Strings, (LPARAM)buff);
				bool noSuchString = true; 
				if (SendMessage(hListBox2, LB_GETCOUNT, NULL, NULL) == 0)
					SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)buff);
				else
				{
					for (int i = 0; i < SendMessage(hListBox2, LB_GETCOUNT, NULL, NULL); i++) {
						if (SendMessage(hListBox2, LB_FINDSTRINGEXACT, i, (LPARAM)buff) != LB_ERR)
							noSuchString = false;
					}
					if (noSuchString)
						SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM)buff);
				}
			}
			break;
			case 59:
			{
				int LB1Strings = SendMessage(hListBox1, LB_GETCARETINDEX, NULL, NULL), LB2Strings = SendMessage(hListBox2, LB_GETCARETINDEX, NULL, NULL);
				SendMessage(hListBox1, LB_DELETESTRING, LB1Strings, 0);
				SendMessage(hListBox2, LB_DELETESTRING, LB2Strings, 0);
			}
			break;
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
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
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
