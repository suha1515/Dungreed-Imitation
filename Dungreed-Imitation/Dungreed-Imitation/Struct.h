#pragma once
struct Vertex
{
	Vertex() = default;
	Vertex(Vector2 _pos, Vector2 _tex, mRGB _color = mRGB(0.f, 0.f, 0.f)) :pos(_pos), tex(_tex), color(_color) {}

	Vector2 pos;
	Vector2 tex;
	mRGB color;
};

typedef struct Info
{
	Vector2 pos;
	Vertex vertex[4];
	Vertex copy_vertex[4];
	
	float fCX = 0.f;
	float fCY = 0.f;
}INFO;

typedef struct AnimationInfo
{
	AnimationInfo() {};
	int widthCount;
	int heightCount;
}ANIM_INFO;