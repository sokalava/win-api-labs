#include <iostream>
#include <windows.h>++++ 


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //Вот эта функция WndProc и будет получать сообщения, которые Windows будет отсылать окну.
LRESULT CALLBACK WndChildProc(HWND, UINT, WPARAM, LPARAM); //дочернее окно 
TCHAR mainMessage[] = L"Hellow, World!"; //символьный тип 
RECT rc;
HWND hChildWnd; // открытие дочернего окна 


int WINAPI WinMain(HINSTANCE hInst,// указатель на текущий экземпляр
	HINSTANCE hPrevInstance,// указатель на предыдущйи запушенный экземпляр
	LPSTR lpCmdLine,// командная строка
	int nCmdShow)// тип отображения окна программы
{
	TCHAR szClassName[] = L"Мой класс";
	HWND hMainWnd; //Идентификатор окна
	MSG msg; 
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = hInst;
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
		return NULL;
	}
	WNDCLASSEX wc1;
	wc1.cbSize = sizeof(wc1);
	wc1.style = CS_HREDRAW | CS_VREDRAW;
	wc1.lpfnWndProc = WndChildProc;
	wc1.lpszMenuName = NULL;
	wc1.lpszClassName = L"ФЦВ";
	wc1.cbWndExtra = NULL;
	wc1.cbClsExtra = NULL;
	wc1.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc1.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc1.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc1.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc1.hInstance = hInst;
	if (!RegisterClassEx(&wc1)) {

		MessageBox(NULL, L"Не получилось зарегистрировать класс2!", L"Ошибка", MB_OK);
		return NULL;
	}

	hMainWnd = CreateWindow(
		L"Мой класс",
		L"Полноценная оконная процедура",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,
		CW_USEDEFAULT,
		NULL,
		CW_USEDEFAULT,
		NULL,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInst),
		NULL);
	GetClientRect(hMainWnd, &rc);
	hChildWnd = CreateWindow(
		L"ФЦВ",
		L"Дочернее окно",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_POPUP,
		850,
		25,
		rc.right / 2,
		rc.bottom / 2,
		hMainWnd,
		NULL,
		HINSTANCE(hInst),
		NULL);
	if (!hMainWnd) {
		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
		return NULL;
	}
	ShowWindow(hMainWnd, SW_MAXIMIZE);
	ShowWindow(hChildWnd, nCmdShow);
	UpdateWindow(hChildWnd);
	UpdateWindow(hMainWnd);
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	RECT rect;
	COLORREF colorText = RGB(255, 127, 127);
	switch (uMsg) {
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetTextColor(hDC, colorText);
		DrawText(hDC, mainMessage, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	case WM_RBUTTONDOWN:
		ShowWindow(hChildWnd, SW_MINIMIZE);
		break;
	case WM_LBUTTONDOWN:
		ShowWindow(hChildWnd, SW_NORMAL);
		MoveWindow(hChildWnd, 850, 25, rc.right / 2, rc.bottom / 2, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}
LRESULT CALLBACK WndChildProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


