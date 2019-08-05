#pragma once
struct Vertex
{
	Vertex(CVector2 _pos, CVector2 _tex, mRGB _color) :pos(_pos), tex(_tex), color(_color) {}

	CVector2 pos;
	CVector2 tex;
	mRGB color;
};

struct Info
{
	float fX = 0.f;
	float fY = 0.f;
	float fCX = 0.f;
	float fCY = 0.f;
};