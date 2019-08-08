#pragma once

#ifndef __EXTERN_H__

// extern 키워드: 외부에 이러한 전역변수가 존재함을 알려주는 키워드.
extern HWND g_hWnd;
extern HDC	g_hDC;
extern HDC	BackDC;
extern HINSTANCE hInst;

extern HDC BackDC;
extern float g_fDeltaTime;

#define __EXTERN_H__
#endif