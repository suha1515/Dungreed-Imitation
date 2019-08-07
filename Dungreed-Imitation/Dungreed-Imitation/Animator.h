#pragma once

class Animator
{
public:
	Animator();
	~Animator();
public:
	void Initialize();

public:
	void SetInfo(int heightCount,int widthCount);
	void MakeClip(const wstring&  imgName, int sizeX, int sizeY);

public:
	void PlayAnim(Renderer * render, const wstring & clipName,Vertex* vertex, ANIMATION_TYPE type, float speed);

private:
	int animStart;
	int animEnd;
	float animTime;

	float animXGap;
	float animYGap;
	map<wstring, ANIM_INFO> m_Clips;
};

