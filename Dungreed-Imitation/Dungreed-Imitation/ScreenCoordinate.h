#pragma once
class ScreenCoordinate
{
public:
	Vector2 _axsis0;
	Vector2 _axsis1;
	Vector2 _origin;

public:
	ScreenCoordinate() :_axsis0(Vector2(1, 0)), _axsis1(Vector2(0, -1)), _origin(Vector2(0, 0)) {}
	void SetInfo(const Vector2& _tAxis0, const Vector2& _tAxsis1, const Vector2& _tOrigin)
	{
		_axsis0 = _tAxis0;
		_axsis1 = _tAxsis1;
		_origin = _tOrigin;
	}
	void SetOrigin(const Vector2& _torigin) { _origin = _torigin; }
	Vector2 Transform(const Vector2& _input)
	{
		Vector2 t0 = _input.x*_axsis0;
		Vector2 t1 = _input.y*_axsis1;
		Vector2 temp(t0.x + t1.x + _origin.x, t0.y + t1.y + _origin.y);
		return temp;
	}
};