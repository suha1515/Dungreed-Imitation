#pragma once
struct Vertex
{
	Vertex() = default;
	Vertex(CVector2 _pos, CVector2 _tex, mRGB _color = mRGB(0.f,0.f,0.f)) :pos(_pos), tex(_tex), color(_color) {}

	CVector2 pos;
	CVector2 tex;
	mRGB color;
};

typedef struct Info
{
	CVector2 pos;
	Vertex texpos[4];
	float fCX = 0.f;
	float fCY = 0.f;
}INFO;