#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<locale.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("window"); //Ÿ��Ʋ�Է�

//�Ʒ� �� ���� �߰��Ⱥκ�.............
//HDC GetDC(HWND hWnd);                      
//int ReleaseDC(HWND hWnd, HDC hDC);
//...................................
/*-----------------------------------------------

�ѱ��� �������ö� �ذ��

#include<locale.h> ��Ŭ���.
�Է¹ޱ� ��
_wsetlocale(LC_ALL, L"Korean"); �ڵ� �Է�.

------------------------------------------------*/
char buf[256] = { 0 };
wchar_t buf2[256] = { 0 };
FILE * scn = fopen("scn.txt", "rt");
char * text;
TCHAR buf3[] = { 0 };
int i = 0;
// char to LPCWSTR
void CharToWChar(const char* pstrSrc, wchar_t pwstrDest[])
{
	int nLen = (int)strlen(pstrSrc) + 1;
	mbstowcs(pwstrDest, pstrSrc, nLen);
}

/*scn�� �ؽ�Ʈ�� �о�ͼ� ptr �����ͷ� �ű�� �Լ�...��� �����Ѵ�.*/
char * ReadScn(char * ptr)
{
	fgets(ptr, 256, scn);
	return ptr;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{

	switch (iMessage) 
	{
		while (i<5)
		{

	case WM_LBUTTONDOWN:
	{
		//InvalidateRect(hWnd, NULL, TRUE);
		HDC hdc;
		hdc = GetDC(hWnd);
		_wsetlocale(LC_ALL, L"Korean");
		ReadScn(buf);
		//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, char, strlen(buf), buf3, 256);
		CharToWChar(buf, buf2);
		TextOut(hdc, 320, 300, buf2, lstrlen(buf2)); //�о�鿩�� �����.
		//TCHAR*str = TEXT("beautiful korea");
		//TextOut(hdc, 320, 240, str, lstrlen(str));
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	i++;
		}
	case WM_CREATE:
	{
		CreateWindow(TEXT("button"), TEXT("Ŭ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 20, 100, 25, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("Ŭ��2"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 20, 50, 100, 25, hWnd, (HMENU)1, g_hInst, NULL);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case 0:
			MessageBox(hWnd, TEXT("ù��° ��ư Ŭ��"), TEXT("Button"), MB_OK);
			break;
		case 1:
			MessageBox(hWnd, TEXT("�ι�° ��ư Ŭ��"), TEXT("Button"), MB_OK);
			break;
		}
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		fclose(scn);
		return 0;
		}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}
//[��ó] [API] ��ư ����� ���� | �ۼ��� ��ư ������P