#pragma once
class ScreenCoordinate
{
public:
	CVector2 _axsis0;
	CVector2 _axsis1;
	CVector2 _origin;

public:
	ScreenCoordinate() :_axsis0(CVector2(1, 0)), _axsis1(CVector2(0, -1)), _origin(CVector2(0, 0)) {}
	void SetInfo(const CVector2& _tAxis0, const CVector2& _tAxsis1, const CVector2& _tOrigin)
	{
		_axsis0 = _tAxis0;
		_axsis1 = _tAxsis1;
		_origin = _tOrigin;
	}
	void SetOrigin(const CVector2& _torigin) { _origin = _torigin; }
	CVector2 Transform(const CVector2& _input)
	{
		CVector2 t0 = _input.x*_axsis0;
		CVector2 t1 = _input.y*_axsis1;
		CVector2 temp(t0.x + t1.x + _origin.x, t0.y + t1.y + _origin.y);
		return temp;
	}
};