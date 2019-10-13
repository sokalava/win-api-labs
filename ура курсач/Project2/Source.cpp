#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <iostream>
#include "RPN.h"

#pragma comment (lib, "Shlwapi.lib") 

static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Калькулятор (Lab2)");
char buf[256], buf1[256], buf2[256];
long double fact(int N)
{
	if (N < 0) // если пользователь ввел отрицательное число
		return 0; // возвращаем ноль
	if (N == 0) // если пользователь ввел ноль,
		return 1; // возвращаем факториал от нуля - не удивляетесь, но это 1 =)
	else // Во всех остальных случаях
		return N * fact(N - 1); // делаем рекурсию.
}
HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Главная часть программы-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	// ------------------------------------------------------------------------------------------------------------

	// Структура класса окна---------------------------------------------------------------------------------------
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 25);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
	// ------------------------------------------------------------------------------------------------------------

	// Регистрируем класс окна------------------------------------------------------------------------------------
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			0);
		return 1;
	}
	// ------------------------------------------------------------------------------------------------------------

	// Создаём окно---------------------------------------------------------------------------------------
	hInst = hInstance;

	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		360, 300,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			0);
		return 1;
	}
	// ------------------------------------------------------------------------------------------------------------

	// Отображаем окно---------------------------------------------------------------------------------------------
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// ------------------------------------------------------------------------------------------------------------

	// Цикл обработки сообщений для прослушивания отправляемых ОС сообщений----------------------------------------
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}
// ------------------------------------------------------------------------------------------------------------

// Функция------------------------------------------------------------------------------------------------------------
#define ID_EDIT  99
#define ID_BUTTON    100
#define ID_BUTTON_1  101
#define ID_BUTTON_2  102
#define ID_BUTTON_3  103
#define ID_BUTTON_4  104
#define ID_BUTTON_5  105
#define ID_BUTTON_6  106
#define ID_BUTTON_7  107
#define ID_BUTTON_8  108
#define ID_BUTTON_9  109
#define ID_BUTTON_ADD    110
#define ID_BUTTON_SUB    111
#define ID_BUTTON_MUL    112
#define ID_BUTTON_DIV    113
#define ID_BUTTON_RES   114
#define ID_BUTTON_C    115
#define ID_BUTTON_COS 117
#define ID_BUTTON_SIN 118
#define ID_BUTTON_TAN 119
#define ID_BUTTON_X2 120
#define ID_BUTTON_XY 121
#define ID_BUTTON_LOG 122
#define ID_BUTTON_10X 123
#define ID_BUTTON_PI 124
#define ID_BUTTON_DOT 125
#define ID_BUTTON_BACKSPASE 126
#define ID_BUTTON_PM 127
#define ID_BUTTON_1X 128
#define ID_BUTTON_FACT 129
#define ID_BUTTON_EX 130
#define ID_BUTTON_LN 131
#define ID_BUTTON_SQRT 132
#define ID_BUTTON_HEX 133
#define ID_BUTTON_DEC 134
#define ID_BUTTON_OCT 135
#define ID_BUTTON_BIN 136


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Структура класса кнопки-------------------------------------------------------------------------------------
	static bool resB;
	static HWND hButton[100], hEdit, hListBox;
	static bool dot, two, dot2;
	static int func = 0;
	PAINTSTRUCT ps;
	HDC hdc;
	int i = 0;
	int count = 0, a = 0, b = 0;
	// ------------------------------------------------------------------------------------------------------------
	switch (message)
	{
	case WM_CREATE:
		hEdit = CreateWindow(_T("listbox"), _T("0"), WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 5, 333, 37, hWnd, (HMENU)ID_EDIT, hInst, 0);
		hButton[0] = CreateWindow(_T("Button"), _T("0"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 95, 225, 90, 30, hWnd, (HMENU)ID_BUTTON, hInst, 0);
		hButton[1] = CreateWindow(_T("Button"), _T("1"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 95, 190, 40, 30, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
		hButton[2] = CreateWindow(_T("Button"), _T("2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 145, 190, 40, 30, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
		hButton[3] = CreateWindow(_T("Button"), _T("3"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 195, 190, 40, 30, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
		hButton[4] = CreateWindow(_T("Button"), _T("4"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 95, 155, 40, 30, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
		hButton[5] = CreateWindow(_T("Button"), _T("5"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 145, 155, 40, 30, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
		hButton[6] = CreateWindow(_T("Button"), _T("6"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 195, 155, 40, 30, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
		hButton[7] = CreateWindow(_T("Button"), _T("7"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 95, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
		hButton[8] = CreateWindow(_T("Button"), _T("8"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 145, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
		hButton[9] = CreateWindow(_T("Button"), _T("9"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 195, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
		hButton[10] = CreateWindow(_T("Button"), _T("+"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 245, 155, 43, 30, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
		hButton[11] = CreateWindow(_T("Button"), _T("-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 295, 155, 43, 30, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
		hButton[12] = CreateWindow(_T("Button"), _T("*"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 245, 190, 43, 30, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
		hButton[13] = CreateWindow(_T("Button"), _T("/"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 295, 190, 43, 30, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
		hButton[14] = CreateWindow(_T("Button"), _T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 245, 225, 93, 30, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
		hButton[15] = CreateWindow(_T("Button"), _T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 245, 115, 93, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
		hButton[16] = CreateWindow(_T("Button"), _T("."), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 195, 225, 40, 30, hWnd, (HMENU)ID_BUTTON_DOT, hInst, 0);
		hButton[17] = CreateWindow(_T("Button"), _T("cos"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_COS, hInst, 0);
		hButton[18] = CreateWindow(_T("Button"), _T("sin"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_SIN, hInst, 0);
		hButton[19] = CreateWindow(_T("Button"), _T("tan"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_TAN, hInst, 0);
		hButton[20] = CreateWindow(_T("Button"), _T("x^2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_X2, hInst, 0);
		hButton[21] = CreateWindow(_T("Button"), _T("x^y"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_XY, hInst, 0);
		hButton[22] = CreateWindow(_T("Button"), _T("log"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 115, 40, 30, hWnd, (HMENU)ID_BUTTON_LOG, hInst, 0);
		hButton[23] = CreateWindow(_T("Button"), _T("10^x"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 150, 40, 30, hWnd, (HMENU)ID_BUTTON_10X, hInst, 0);
		hButton[24] = CreateWindow(_T("Button"), _T("Pi"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 150, 40, 30, hWnd, (HMENU)ID_BUTTON_PI, hInst, 0);
		hButton[25] = CreateWindow(_T("Button"), _T("+-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 190, 40, 30, hWnd, (HMENU)ID_BUTTON_PM, hInst, 0);
		hButton[26] = CreateWindow(_T("Button"), _T("sqrt"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 190, 40, 30, hWnd, (HMENU)ID_BUTTON_SQRT, hInst, 0);
		hButton[27] = CreateWindow(_T("Button"), _T("1/x"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 5, 225, 40, 30, hWnd, (HMENU)ID_BUTTON_1X, hInst, 0);
		hButton[28] = CreateWindow(_T("Button"), _T("n!"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 225, 40, 30, hWnd, (HMENU)ID_BUTTON_FACT, hInst, 0);
		hButton[29] = CreateWindow(_T("Button"), _T("e^x"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 95, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_EX, hInst, 0);
		hButton[30] = CreateWindow(_T("Button"), _T("ln"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 145, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_LN, hInst, 0);
		hButton[31] = CreateWindow(_T("Button"), _T("HEX"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 95, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_HEX, hInst, 0);
		hButton[32] = CreateWindow(_T("Button"), _T("OCT"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 145, 45, 40, 30, hWnd, (HMENU)ID_BUTTON_OCT, hInst, 0);
		hButton[36] = CreateWindow(_T("Button"), _T("BIN"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 195, 80, 40, 30, hWnd, (HMENU)ID_BUTTON_BIN, hInst, 0);
		hButton[37] = CreateWindow(_T("Button"), _T("<-"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 245, 80, 93, 30, hWnd, (HMENU)ID_BUTTON_BACKSPASE, hInst, 0);
		buf[0] = '0';
		buf2[0] = '0';
		SendMessage(hEdit, LB_ADDSTRING, 0, (LPARAM)buf);
		//hButton[31] = CreateWindow(_T("Button"), _T(""), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 295, 80, 43, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
		break;
	case WM_COMMAND:
		if ((LOWORD(wParam) == ID_BUTTON) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("0"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '0';
					buf[1] = 0;
					resB = false;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("0"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("1"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '1';
					buf[1] = 0;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = false;
					dot = false;
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("1"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("2"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '2';
					buf[1] = 0;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = false;
					dot = false;
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("2"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("3"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '3';
					buf[1] = 0;
					resB = false;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("3"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("4"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '4';
					buf[1] = 0;
					resB = false;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("4"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("5"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '5';
					buf[1] = 0;
					resB = false;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("5"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("6"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '6';
					buf[1] = 0;
					resB = false;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("6"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("7"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '7';
					buf[1] = 0;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = false;
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("7"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("8"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '8';
					buf[1] = 0;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = false;
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("8"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((*buf2 == TEXT('0')) && (buf2[1] == 0))* buf2 = 0;
				StrCat(buf2, TEXT("9"));
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				if (resB == true) {
					buf[0] = '9';
					buf[1] = 0;
					dot = false;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = false;
				}
				else {
					if ((*buf == TEXT('0')) && (buf[1] == 0))* buf = 0;
					StrCat(buf, TEXT("9"));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_DOT) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				if ((buf2[0] != 0) && (dot2 == false)) {
					StrCat(buf2, TEXT("."));
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					dot2 = true;
				}
			}
			else {
				if ((buf[0] != 0) && (dot == false)) {
					StrCat(buf, TEXT("."));
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					dot = true;
				}
			}

		}

		if ((LOWORD(wParam) == ID_BUTTON_ADD) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == false) {
				StrCpy(buf1, buf);
				StrCat(buf1, TEXT("+"));
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf1);
				buf2[0] = '0';
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				two = true;
				func = 1;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_SUB) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == false) {
				StrCpy(buf1, buf);
				StrCat(buf1, TEXT("-"));
				buf2[0] = '0';
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf1);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				two = true;
				func = 2;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_MUL) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == false) {
				StrCpy(buf1, buf);
				StrCat(buf1, TEXT("*"));
				buf2[0] = '0';
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf1);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				two = true;
				func = 3;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_DIV) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == false) {
				StrCpy(buf1, buf);
				StrCat(buf1, TEXT("/"));
				buf2[0] = '0';
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf1);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				two = true;
				func = 4;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_RES) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n, n2;
			double res;
			if (two == true) {
				sscanf_s(buf, "%lf", &n);
				sscanf_s(buf2, "%lf", &n2);
				switch (func)
				{
				case 1: res = n + n2;
					resB = true;
					break;
				case 2:
					res = n - n2;
					resB = true;
					break;
				case 3:
					res = n * n2;
					resB = true;
					break;
				case 5:
					res = pow(n, n2);
					resB = true;
					break;
				case 4:
					if (n2 != 0) {
						res = n / n2;
						resB = true;
					}
					else MessageBox(0, "ERROR", "ERROR", MB_OK);
					break;
					sprintf(buf, "%lf", res);
					buf2[0] = 0;
				}
				if ((func == 4) && (n2 == 0)) {}
				else {
					sprintf(buf, "%lf", res);
					for (int i = 0; i < 256; i++) buf2[i] = 0;
					for (int i = 0; i < 256; i++) buf1[i] = 0;
					two = false;
					dot2 = false;
					dot = true;
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_C) && (HIWORD(wParam) == BN_CLICKED))
		{
			dot = false;
			buf[0] = '0';
			buf[1] = 0;
			buf2[0] = 0;
			SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
			SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
			SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
			SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			func = 0;
			two = false;
		}

		if ((LOWORD(wParam) == ID_BUTTON_BACKSPASE) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (resB != true)
				if (two == true) {
					if (*buf2 != '0')
					{
						if (buf2[strlen(buf2) - 1] == '.') dot2 = false;
						buf2[strlen(buf2) - 1] = '\0';
						if (*buf2 == '\0') buf2[0] = '0';
						SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
						SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					}

				}
				else {
					if (*buf != '0')
					{
						if (buf[strlen(buf) - 1] == '.') dot = false;
						buf[strlen(buf) - 1] = '\0';
						if (*buf == '\0') buf[0] = '0';
						SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
						SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					}
				}
		}

		if ((LOWORD(wParam) == ID_BUTTON_PM) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = -n;
				if (dot == false) {
					sprintf(buf2, "%d", (int)res);
				}
				else {
					sprintf(buf2, "%lf", res);
					while (buf2[strlen(buf) - 1] == '0') buf2[strlen(buf) - 1] = 0;
					dot2 = true;
				}
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = -n;
				if (dot == false) {
					sprintf(buf, "%d", (int)res);
				}
				else {
					sprintf(buf, "%lf", res);
					while (buf[strlen(buf) - 1] == '0') buf[strlen(buf) - 1] = 0;
					dot = true;
				}
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_COS) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = cos(n);
				sprintf(buf2, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = cos(n);
				sprintf(buf, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				dot = true;
				resB = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_SIN) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = sin(n);
				sprintf(buf2, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = sin(n);
				sprintf(buf, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				resB = true;
				dot = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_TAN) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = tan(n);
				sprintf(buf2, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = tan(n);
				sprintf(buf, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				resB = true;
				dot = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_LOG) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				if (n > 0) {
					res = log10(n);
					sprintf(buf2, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					dot2 = true;
					SendMessage(hButton[14], BM_CLICK, TRUE, 0L);
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);
			}
			else {
					sscanf_s(buf, "%lf", &n);
				if (n > 0) {
					res = log10(n);
					sprintf(buf, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = true;
					dot = true;
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_X2) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = pow(n, 2);
				sprintf(buf2, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = pow(n, 2);
				sprintf(buf, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				resB = true;
				dot = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_10X) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = pow(10.0, n);
				sprintf(buf2, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = pow(10.0, n);
				sprintf(buf, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				resB = true;
				dot = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_PI) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == true) {
				strcpy(buf2, "3.14159265359");
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				strcpy(buf, "3.14159265359");
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				resB = true;
				dot = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_1X) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				if (n == 0) MessageBox(0, "ERROR", "ERROR", MB_OK);
				else {
					res = 1 / n;
					sprintf(buf2, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					dot2 = true;
					SendMessage(hButton[14], BM_CLICK, TRUE, 0L);
				}

			}
			else {
				sscanf_s(buf, "%lf", &n);
				if (n == 0) MessageBox(0, "ERROR", "ERROR", MB_OK);
				else {
					res = 1 / n;
					sprintf(buf, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = true;
					dot = true;
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_FACT) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = fact(n);
				if ((res == 0) || (dot2 == true)) MessageBox(0, "ERROR", "ERROR", MB_OK);
				else {
					sprintf(buf2, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					dot2 = true;
					SendMessage(hButton[14], BM_CLICK, TRUE, 0L);
				}

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = fact(n);
				if ((res == 0) || (dot == true)) MessageBox(0, "ERROR", "ERROR", MB_OK);
				else {
					sprintf(buf, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = true;
					dot = true;
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_EX) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				res = exp(n);
				sprintf(buf2, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				dot2 = true;
				SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				res = exp(n);
				sprintf(buf, "%lf", res);
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
				resB = true;
				dot = true;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_LN) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				if (n > 0) {
					res = log(n);
					sprintf(buf2, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					dot2 = true;
					SendMessage(hButton[14], BM_CLICK, TRUE, 0L);
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);

			}
			else {
				sscanf_s(buf, "%lf", &n);
				if (n > 0) {
					res = log(n);
					sprintf(buf, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = true;
					dot = true;
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_SQRT) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			double res;
			if (two == true) {
				sscanf_s(buf2, "%lf", &n);
				if (n < 0) MessageBox(0, "ERROR", "ERROR", MB_OK);
				else {
					res = sqrtl(n);
					sprintf(buf2, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
					dot2 = true;
					SendMessage(hButton[14], BM_CLICK, TRUE, 0L);
				}

			}
			else {
				sscanf_s(buf, "%lf", &n);
				if (n < 0) MessageBox(0, "ERROR", "ERROR", MB_OK);
				else {
					res = sqrtl(n);
					sprintf(buf, "%lf", res);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf);
					resB = true;
					dot = true;
				}
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_XY) && (HIWORD(wParam) == BN_CLICKED))
		{
			if (two == false) {
				StrCpy(buf1, buf);
				StrCat(buf1, TEXT("^"));
				SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)buf1);
				buf2[0] = '0';
				SendMessage(hEdit, LB_DELETESTRING, 1, 0L);
				SendMessage(hEdit, LB_INSERTSTRING, 1, (LPARAM)buf2);
				two = true;
				func = 5;
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_HEX) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			char res[256];
			if (two == true) {
				MessageBox(0, "Перевод числа не возможен", "ERROR", MB_OK);
			}
			else {
				if (dot == false) {
					sscanf_s(buf, "%lf", &n);
					_itoa_s((int)n, res, 16);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)res);
					resB = true;
					dot = true;
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_OCT) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			char res[256];
			if (two == true) {
				MessageBox(0, "Перевод числа не возможен", "ERROR", MB_OK);
			}
			else {
				if (dot == false) {
					sscanf_s(buf, "%lf", &n);
					_itoa_s((int)n, res, 8);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)res);
					resB = true;
					dot = true;
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);
			}
		}

		if ((LOWORD(wParam) == ID_BUTTON_BIN) && (HIWORD(wParam) == BN_CLICKED))
		{
			double n;
			char res[256];
			if (two == true) {
				MessageBox(0, "Перевод числа не возможен", "ERROR", MB_OK);
			}
			else {
				if (dot == false) {
					sscanf_s(buf, "%lf", &n);
					_itoa_s((int)n, res, 2);
					SendMessage(hEdit, LB_DELETESTRING, 0, 0L);
					SendMessage(hEdit, LB_INSERTSTRING, 0, (LPARAM)res);
					resB = true;
					dot = true;
				}
				else MessageBox(0, "ERROR", "ERROR", MB_OK);
			}
		}
		SendMessage(hWnd, WM_ACTIVATE, TRUE, 0L);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYUP:
		switch (wParam) {
		case 13:
			SendMessage(hButton[14], BM_CLICK, TRUE, 0L);
			break;
		case 110:
			SendMessage(hButton[16], BM_CLICK, TRUE, 0L);
			break;
		case 48:
			SendMessage(hButton[0], BM_CLICK, TRUE, 0L);
			break;
		case 49:
			SendMessage(hButton[1], BM_CLICK, TRUE, 0L);

			break;
		case 50:
			SendMessage(hButton[2], BM_CLICK, TRUE, 0L);

			break;
		case 51:
			SendMessage(hButton[3], BM_CLICK, TRUE, 0L);

			break;
		case 52:
			SendMessage(hButton[4], BM_CLICK, TRUE, 0L);

			break;
		case 53:
			SendMessage(hButton[5], BM_CLICK, TRUE, 0L);

			break;
		case 54:
			SendMessage(hButton[6], BM_CLICK, TRUE, 0L);

			break;
		case 55:
			SendMessage(hButton[7], BM_CLICK, TRUE, 0L);

			break;
		case 56:
			SendMessage(hButton[8], BM_CLICK, TRUE, 0L);

			break;
		case 57:
			SendMessage(hButton[9], BM_CLICK, TRUE, 0L);

			break;

		case 96:
			SendMessage(hButton[0], BM_CLICK, TRUE, 0L);
			break;
		case 97:
			SendMessage(hButton[1], BM_CLICK, TRUE, 0L);

			break;
		case 98:
			SendMessage(hButton[2], BM_CLICK, TRUE, 0L);

			break;
		case 99:
			SendMessage(hButton[3], BM_CLICK, TRUE, 0L);

			break;
		case 100:
			SendMessage(hButton[4], BM_CLICK, TRUE, 0L);
			break;
		case 101:
			SendMessage(hButton[5], BM_CLICK, TRUE, 0L);
			break;
		case 102:
			SendMessage(hButton[6], BM_CLICK, TRUE, 0L);
			break;
		case 103:
			SendMessage(hButton[7], BM_CLICK, TRUE, 0L);
			break;
		case 104:
			SendMessage(hButton[8], BM_CLICK, TRUE, 0L);
			break;
		case 105:
			SendMessage(hButton[9], BM_CLICK, TRUE, 0L);
			break;
		case 107:
			SendMessage(hButton[10], BM_CLICK, TRUE, 0L);
			break;
		case 109:
			SendMessage(hButton[11], BM_CLICK, TRUE, 0L);
			break;
		case 106:
			SendMessage(hButton[12], BM_CLICK, TRUE, 0L);
			break;
		case 111:
			SendMessage(hButton[13], BM_CLICK, TRUE, 0L);
			break;
		case 8:
			SendMessage(hButton[37], BM_CLICK, TRUE, 0L);
			break;
		case 187:
			SendMessage(hButton[14], BM_CLICK, TRUE, 0L);

			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}