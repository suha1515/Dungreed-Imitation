// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define _USE_MATH_DEFINES				// cmath ������ ����
// Windows ��� ����:
#include <windows.h>


// C ��Ÿ�� ��� �����Դϴ�.
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



// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Define.h"
#include "extren.h"
#include "RGB.h"
#include "BitMap.h"
#include "Rasterizer.h"
#include "typedef.h"
#include "Vector2.h"
#include "Struct.h"


#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

