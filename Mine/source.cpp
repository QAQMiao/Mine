#include <stdio.h>
#include <windows.h>
#include <vector>
#include "IOControl.hpp"
#include "Texture.hpp"
#include "Point.hpp"
using namespace std;

namespace MEOM{
	auto p = MEOM::IOControl::getInstance();
//	RECT g_rect = { 0 };
	HINSTANCE   g_hInst = NULL;
	HWND        hwnd = NULL;
//	HDC			hdc = NULL;
//	HDC 		buffer = NULL;
//	HBITMAP 	bmp;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HDC buf);
	HRESULT InitWindow(HINSTANCE hInstance, int nCmdShow)
	{
		// Register class
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, NULL);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = "CrystalMiao";
		wcex.hIconSm = LoadIcon(wcex.hInstance, NULL);
		if (!RegisterClassEx(&wcex))
			return E_FAIL;

		// Create window
		g_hInst = hInstance;
		RECT rc = { 0, 0, 300, 300 };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		hwnd = CreateWindow("CrystalMiao", "Crystal Miao", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
			rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
		if (!hwnd)
			return E_FAIL;

		ShowWindow(hwnd, nCmdShow);
		return S_OK;
	}

	bool isDown = false;

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{

		//Point pt;
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_MOUSEMOVE:
			if (isDown == false)
			{
				break;
			}
			break;
		case WM_LBUTTONDOWN:
			isDown = true;
			break;
		case WM_LBUTTONUP:
			isDown = false;
			break;
		case WM_KEYDOWN:
			printf("%c", wParam);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		return 0;
	}

	void Render(HDC buf)
	{
		SelectObject(buf, bmp);
		//Add your render code here.
		SelectObject(buf, pen);
		SelectObject(buf, brush);
	}

}
int main()
{
	using namespace MEOM;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	MEOM::Texture tt("./Blank.bmp");

    if(FAILED(InitWindow(hInstance, true)))
        return 0;
    MSG msg = {0};

	GetClientRect(hwnd,&g_rect);
//	hdc = GetDC(hwnd);
//	buffer = CreateCompatibleDC(hdc);
//	bmp = CreateCompatibleBitmap(hdc,g_rect.right,g_rect.bottom);

	while(WM_QUIT != msg.message)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Render(buffer);
			BitBlt(hdc,0,0,g_rect.right - g_rect.left,g_rect.bottom - g_rect.top,buffer,0,0,SRCCOPY);
		}
	}
	return (int)msg.wParam;
}

