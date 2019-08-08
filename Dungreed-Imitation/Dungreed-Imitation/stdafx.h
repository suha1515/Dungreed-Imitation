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
#include<map>
#include<list>
#include<vector>
#include <algorithm>
#include <functional>
#include <objidl.h>
#include <gdiplus.h>
#include <comdef.h>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")
#pragma comment(lib,"winmm.lib")


using namespace std;


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

//�������
#include "Math.h"
#include "Vector2.h"
#include "Matrix2D.h"
#include "Matrix3D.h"
#include "ScreenCoordinate.h"

#include "Define.h"
#include "Enum.h"
#include "Function.h"
#include "Extern.h"
#include "Typedef.h"

#include "RGB.h"
#include "BitMap.h"

#include"Struct.h"
#include"Rasterizer.h"
#include"Renderer.h"
#include "Animator.h"
#include "DrawUtil.h"


//�Ŵ��� ���
#include "ObjectManager.h"
#include "ImageManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

#include "vld.h"

#pragma comment(linker,"/entry:wWinMainCRTStartup /subsystem:console")

