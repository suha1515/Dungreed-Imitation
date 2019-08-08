#include "stdafx.h"
#include "DrawUtil.h"



void DrawUtil::DrawLine(HDC hdc, float x0, float y0, float x1, float y1, int lineWidth, int penStyle, COLORREF color)
{
	DrawLine(hdc, Vector2(x0, y0), Vector2(x1, y1), lineWidth, penStyle, color);
}

void DrawUtil::DrawLine(HDC hdc, const Vector2 & _v0, const Vector2 & _v1, int _lineWidth, int _penStyle, COLORREF _color)
{
	Vector2 v0 = _v0;
	Vector2 v1 = _v1;
	/*v0 = g_basis2.Trasnform(_v0);
	v1 = g_basis2.Trasnform(_v1);
	v0 = g_screenCoordinate.Transform(v0);
	v1 = g_screenCoordinate.Transform(v1);*/

	//여러 그리는 방법이있는데 pen스타일로 그리기를 지정한다.
	//pen 객체를 생성한다.
	HPEN hpen = CreatePen(_penStyle, _lineWidth, _color);
	//GDI 오브젝트를 변경하기위해 해당 dc 핸들값과 바꾸고싶은 GDI 오브젝트의 핸들값을 전달한다.
	//반환값은 기존에있던 오브젝트를 반환한다.
	HGDIOBJ original = SelectObject(hdc, hpen);
	{
		MoveToEx(hdc, (int)v0.x, (int)v0.y, nullptr);
		LineTo(hdc, (int)v1.x, (int)v1.y);
	}
	//반환받은 기존의 오브젝트로 돌린다.
	SelectObject(hdc, original);
	DeleteObject(hpen);
}

void DrawUtil::DrawAxsis(HDC hdc, int _numHorizonGrid, int _numVerticalGrid, COLORREF _color, COLORREF _color2)
{
	{
		Vector2 v0 = Vector2(0, -_numVerticalGrid / 2);
		Vector2 v1 = Vector2(0, _numVerticalGrid / 2);
		DrawUtil::DrawLine(hdc, v0, v1, 2, PS_SOLID, _color);
	}

	{
		Vector2 v0 = Vector2(-(_numHorizonGrid) / 2, 0);
		Vector2 v1 = Vector2((_numHorizonGrid) / 2, 0);
		DrawUtil::DrawLine(hdc, v0, v1, 2, PS_SOLID, _color2);
	}
}

void DrawUtil::DrawGrid(HDC hdc, int _numHorizonGrid, int _numVerticalGrid, COLORREF _color)
{
	//DrawLine(hdc, Vector2(0, 0), Vector2(WINCX, 0),1,0,_color);
	//DrawLine(hdc, Vector2(0, 16), Vector2(WINCX, 16), 1, 0, _color);

	int GapY = 32;
	int GapX = 32;
	for (int count = 0; count <= WINCY/32; ++count)
	{
		Vector2 v0 = Vector2(0, 0) + Vector2(0, GapY*count);
		Vector2 v1 = Vector2(WINCX, 0) + Vector2(0, GapY*count);
		DrawUtil::DrawLine(hdc, v0, v1, 1, PS_SOLID, _color);
	}

	for (int count = 0; count <= WINCX/32; ++count)
	{
		Vector2 v0 = Vector2(0, 0) + Vector2(GapX*count, 0);
		Vector2 v1 = Vector2(0,WINCY) +  Vector2(GapX*count, 0);
		DrawUtil::DrawLine(hdc, v0, v1, 1, PS_SOLID, _color);
	}
}

void DrawUtil::DrawGrid(HDC hdc, int startX, int startY,int endX,int endY,int hLine,int vLine, COLORREF _color)
{
	//DrawLine(hdc, Vector2(0, 0), Vector2(WINCX, 0),1,0,_color);
	//DrawLine(hdc, Vector2(0, 16), Vector2(WINCX, 16), 1, 0, _color);

	int GapY = 32;
	int GapX = 32;
	for (int count = 0; count <=hLine; ++count)
	{
		Vector2 v0 = Vector2(startX, startY) + Vector2(0, GapY*count);
		Vector2 v1 = Vector2(endX, startY) + Vector2(0, GapY*count);
		DrawUtil::DrawLine(hdc, v0, v1, 1, PS_SOLID, _color);
	}

	for (int count = 0; count <= vLine; ++count)
	{
		Vector2 v0 = Vector2(startX, startY) + Vector2(GapX*count, 0);
		Vector2 v1 = Vector2(startX, endY) + Vector2(GapX*count, 0);
		DrawUtil::DrawLine(hdc, v0, v1, 1, PS_SOLID, _color);
	}
}
