// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#define _USE_MATH_DEFINES				// cmath 디파인 사용ㅡ
// Windows 헤더 파일:
#include <windows.h>


// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include<cmath>
#include<iostream>
#include<string>
#include <objidl.h>
#include <gdiplus.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib,"winmm.lib")


using namespace std;



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Define.h"
#include "extren.h"
#include "RGB.h"
#include "BitMap.h"
#include "Rasterizer.h"
#include "typedef.h"
#include "Vector2.h"
#include "Struct.h"


#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

