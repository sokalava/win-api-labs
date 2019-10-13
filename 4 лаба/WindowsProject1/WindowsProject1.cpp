#include <windows.h>

ATOM RegisterWndClass(HINSTANCE hInstance, LPCWSTR lpszClassName);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{
	HWND hWnd;
	MSG uMsg;
	LPCWSTR lpszClassName = L"Drawing with the Mouse";
	LPCWSTR lpszWindowName = L"Lab2";

	if (!RegisterWndClass(hInstance, lpszClassName))
	{
		MessageBox(NULL, L"Window Registration Failed!", NULL,
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	hWnd = CreateWindowExW(
		WS_EX_OVERLAPPEDWINDOW,
		lpszClassName,
		lpszWindowName,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", NULL,
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	while (GetMessage(&uMsg, NULL, 0, 0))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}

	return (INT)uMsg.wParam;
}

ATOM RegisterWndClass(HINSTANCE hInstance, LPCWSTR lpszClassName)
{
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbClsExtra = 0;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	return RegisterClassEx(&wndClass);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int iCount, iPrevX, iPrevY;
	static HDC hDc, hOldPen;
	static HPEN hPen;

	PAINTSTRUCT ps;
	RECT rect;

	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		iCount = 0;
		iPrevX = LOWORD(lParam);
		iPrevY = HIWORD(lParam);
	}
	break;

	case WM_MOUSEMOVE:
	{
		if (wParam == MK_LBUTTON)
		{
			hDc = GetDC(hWnd);
			hOldPen = (HDC)SelectObject(hDc, hPen);
			MoveToEx(hDc, iPrevX, iPrevY, NULL);
			LineTo(hDc, LOWORD(lParam), HIWORD(lParam));
			iPrevX = LOWORD(lParam);
			iPrevY = HIWORD(lParam);
			ReleaseDC(hWnd, hDc);
		}
	}
	break;

	case WM_LBUTTONUP:
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_PAINT:
	{
		GetClientRect(hWnd, &rect);
		hDc = BeginPaint(hWnd, &ps);
		InvalidateRect(hWnd, &rect, FALSE);
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_F1:
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			break;

		case VK_F2:
			hPen = CreatePen(PS_SOLID, 6, RGB(0, 255, 0));
			break;

		case VK_F3:
			hPen = CreatePen(PS_SOLID, 11, RGB(0, 0, 255));
			break;
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}