#pragma once
namespace DrawUtil
{
	void DrawLine(HDC hdc, float x0, float y0, float x1, float y1, int lineWidth, int penStyle, COLORREF color);
	void DrawLine(HDC hdc, const Vector2& _v0, const Vector2& _v1, int _lineWidth = 1, int _penStyle = PS_SOLID, COLORREF _color = RGB(0, 0, 0));
	void DrawAxsis(HDC hdc, int _numHorizonGrid, int _numVerticalGrid, COLORREF _color = RGB(64, 64, 64), COLORREF _color2 = RGB(64, 64, 64));
	void DrawGrid(HDC hdc, int _numHorizonGrid, int _numVerticalGrid, COLORREF _color = RGB(64, 64, 64));
	void DrawGrid(HDC hdc, int startX, int startY, int endX, int endY, int hLine, int vLine, COLORREF _color);
}