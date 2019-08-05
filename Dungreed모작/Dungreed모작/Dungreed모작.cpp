// Dungreed����.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Renderer.h"
#include "Timer.h"
#include "Dungreed����.h"


#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;                                // ���� �ν��Ͻ��Դϴ�.
WCHAR szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

CRasterizer screen;
CBitMap		bitmap;
CBitMap		bitmap2;
Renderer    render;

//��������
HWND g_hWnd;
HDC m_hdc;
Bitmap*	g_image;

//Ÿ�̸�
CTimer mTimer;

void OnIdle();
void CalculateFrameStats();
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DUNGREED, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DUNGREED));
	MSG msg;

	mTimer.Reset();

	while (true)
	{
		::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		const BOOL bIsTranslateMessage = TranslateAccelerator(msg.hwnd, hAccelTable, &msg);
		if (!bIsTranslateMessage)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		mTimer.Tick();
		CalculateFrameStats();
		OnIdle();
		if (msg.message == WM_QUIT)
			break;

	}
   
	GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}



//
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DUNGREED));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DUNGREED);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINCX,WINCY, nullptr, nullptr, hInstance, nullptr);
   
   if (!hWnd)
   {
      return FALSE;
   }
   g_hWnd = hWnd;
   m_hdc = GetDC(hWnd);
   RECT clientRect;

   ::GetClientRect(hWnd, &clientRect);
   int iWidth = clientRect.right - clientRect.left + 1;
   int iHeight = clientRect.bottom - clientRect.top + 1;
   screen.CreateDIB(m_hdc, iWidth, iHeight);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //�׸����ϵ�
   bitmap.ReadBitMap("..//texture//1.bmp");
   bitmap2.ReadBitMap("..//texture//800x600.bmp");
   g_image = new Bitmap(L"..//texture//1.bmp");
   render.SetRasterizer(&screen);
   render.SetColorMask(mRGB(1.f, 0.f, 1.f));
   
   return TRUE;
}

//
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ带 �߰��մϴ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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

void OnIdle()
{
	screen.ClearScreen();
	/*screen.SetPixel(100, 100, mRGB(0.5f, 0.5f, 0.5f));
	screen.SetPixel(100, 101, mRGB(1.f,0,0));*/
	render.DrawBitMap(0,0, &bitmap2);

	Vertex p1(CVector2(200.f, 200.0f), CVector2(0.f,0.f), mRGB(1.f, 0.f, 0.f));
	Vertex p2(CVector2(200.f, 350.0f), CVector2(0.f,1.f), mRGB(0.f, 1.f, 0.f));
	Vertex p3(CVector2(400.f, 350.0f), CVector2(1.f,1.f), mRGB(0.f, 0.f, 1.f));
	Vertex p4(CVector2(400.f, 200.0f), CVector2(1.f,0.f), mRGB(0.f, 0.f, 1.f));

	//render.DrawTriangleBarycentric(p1, p2, p3);
	render.DrawTriangleBarycentric(p1, p2, p3, &bitmap);
	render.DrawTriangleBarycentric(p3, p4, p1, &bitmap);

	render.DrawBitMap(100, 100, &bitmap);
	//render.DrawTriangleBarycentric(p1, p2, p3, g_image);
	//render.DrawTriangleBarycentric(p3, p4, p1, g_image);
	screen.Present(&m_hdc);
}

void CalculateFrameStats()
{
	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	if ((mTimer.TotalTIme() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		TCHAR buffer[100];
		swprintf_s(buffer, TEXT("%s FPS : %f"), szTitle, fps);
		SetWindowText(g_hWnd, buffer);
		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}