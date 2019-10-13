
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>

LRESULT CALLBACK WindowProcess(HWND, UINT, WPARAM, LPARAM);
int check(char str[100], int a)
{
	if ((str[0]<'A' || str[0]>'Z') && (str[0]<'А' || str[0]>'Я')) return 0;
	if (a == 1)
	{
		int tire = 0;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] == '-') tire++;
			if (str[i] == '-' && (i == 0 || i == (strlen(str) - 1))) return 0;
			if (((str[i]<'A' || str[i]>'Z') && (str[i]<'a' || str[i]>'z')) && ((str[i]<'А' || str[i]>'Я') && (str[i]<'а' || str[i]>'я')) && str[i] != '-') return 0;
		}
		if (tire > 1) return 0;
		return 1;
	}
	for (int i = 0; i < strlen(str); i++)
	{
		if (((str[i]<'A' || str[i]>'Z') && (str[i]<'a' || str[i]>'z')) && ((str[i]<'А' || str[i]>'Я') && (str[i]<'а' || str[i]>'я'))) return 0;
	}
	return 1;
}
HINSTANCE hInst;
HWND scroll;
HWND hMain;
HWND btn;
HWND edit1, edit2, edit3, edit4;
RECT rect;
HDC hDC;
int count = 1;
char Count[3] = "";
char Count2[20] = "";

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR pCommandLine,
	int nCommandShow) {
	TCHAR className[] = L"Мой класс";
	HWND hWindow;
	MSG message;
	WNDCLASSEX windowClass;

	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = className;
	windowClass.cbWndExtra = NULL;
	windowClass.cbClsExtra = NULL;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.hInstance = hInst;

	if (!RegisterClassEx(&windowClass))
	{
		MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
		return NULL;
	}
	hWindow = CreateWindow(className,
		L"Программа (вариант 21)",
		WS_OVERLAPPEDWINDOW,
		500,
		250,
		360,
		320,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInst),
		NULL);

	if (!hWindow) {
		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
		return NULL;
	}
	ShowWindow(hWindow, nCommandShow);

	UpdateWindow(hWindow);

	while (GetMessage(&message, NULL, NULL, NULL)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	return message.wParam;
}


LRESULT CALLBACK WindowProcess(HWND hWindow,
	UINT uMessage,
	WPARAM wParameter,
	LPARAM lParameter)
{
	static int sPos, sMin, sMax;
	PAINTSTRUCT ps;
	HANDLE File;
	DWORD dwCount;
	char SecondName[100] = "", FirstName[100] = "", OtchestvoName[100] = "", number[5] = "";
	switch (uMessage)
	{
	case WM_CREATE:
		edit1 = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL, 130, 25, 190, 25, hWindow, NULL, hInst, NULL);
		ShowWindow(edit1, SW_SHOWNORMAL);
		edit2 = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL, 130, 70, 190, 25, hWindow, NULL, hInst, NULL);
		ShowWindow(edit2, SW_SHOWNORMAL);
		edit3 = CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_AUTOHSCROLL, 130, 120, 190, 25, hWindow, NULL, hInst, NULL);
		ShowWindow(edit3, SW_SHOWNORMAL);
		edit4 = CreateWindow(L"edit", L"1", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY | ES_AUTOHSCROLL, 130, 170, 170, 50, hWindow, NULL, hInst, NULL);
		ShowWindow(edit4, SW_SHOWNORMAL);
		btn = CreateWindow(L"button", L"Сохранить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 120, 235, 100, 25, hWindow, NULL, hInst, NULL);
		ShowWindow(btn, SW_SHOWNORMAL);
		scroll = CreateWindowEx(0, L"SCROLLBAR", (PTSTR)NULL, WS_CHILD | WS_VISIBLE | SBS_VERT, 305, 177, 17, 34, hWindow, NULL, hInst, NULL);
		SendMessage(btn, BM_SETSTATE, TRUE, 0);
		break;
	case WM_VSCROLL:
	{
		switch (LOWORD(wParameter))
		{
		case SB_LINEUP:
		{
			if (count != 10)
			{
				count++;
				strcpy_s(Count, "");
				_itoa_s(count, Count, 10);
				SendMessageA(edit4, WM_SETTEXT, 0, (LPARAM)(Count));
			}
			break;
		}
		case SB_LINEDOWN:
		{
			if (count != 1)
			{
				count--;
				strcpy_s(Count, "");
				_itoa_s(count, Count, 10);
				SendMessageA(edit4, WM_SETTEXT, 0, (LPARAM)(Count));
			}
			break;
		}
		}
		break;
	}
	case WM_PAINT:
		hDC = BeginPaint(hWindow, &ps);
		TextOut(hDC, 55, 30, L"Фамилия:", 18);
		TextOut(hDC, 90, 74, L"Имя:", 8);
		TextOut(hDC, 55, 124, L"Отчество:", 9);
		TextOut(hDC, 69, 174, L"Оценка:", 9);
		EndPaint(hWindow, &ps);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:

		SendMessage(btn, BM_SETSTATE, TRUE, 0);
		GetWindowTextA(edit1, SecondName, 100);
		GetWindowTextA(edit2, FirstName, 100);
		GetWindowTextA(edit3, OtchestvoName, 100);
		if ((strlen(SecondName) != 0 && SecondName[0] != ' ') && (strlen(FirstName) != 0 && FirstName[0] != ' ') && (strlen(OtchestvoName) != 0 && OtchestvoName[0] != ' '))
		{
			SendMessage(btn, BM_SETSTATE, FALSE, 0);
			if (lParameter == (LPARAM)btn)
			{
				if (!check(SecondName, 1) || !check(FirstName, 0) || !check(OtchestvoName, 0))
				{
					MessageBox(NULL, L"Вы ввели неверно! Введите снова!", L"Ошибка", MB_OK);
					break;
				}
				File = CreateFile(L"list.txt", GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				SetFilePointer(File, 0, 0, FILE_END);
				GetWindowTextA(edit4, number, 5);
				WriteFile(File, SecondName, (strlen(SecondName) * sizeof(char)) + sizeof(char), &dwCount, NULL);
				WriteFile(File, FirstName, (strlen(FirstName) * sizeof(char)) + sizeof(char), &dwCount, NULL);
				WriteFile(File, OtchestvoName, (strlen(OtchestvoName) * sizeof(char)) + sizeof(char), &dwCount, NULL);
				WriteFile(File, number, strlen(number) * sizeof(char), &dwCount, NULL);
				WriteFile(File, "\n", sizeof(char), &dwCount, NULL);
				CloseHandle(File);
			}
		}

		break;
	default:
		return DefWindowProc(hWindow, uMessage, wParameter, lParameter);
	}
	return NULL;
}