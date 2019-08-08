#pragma once

class Animator
{
public:
	Animator();
	~Animator();
public:
	void Initialize();
	void Release();

public:
	void SetInfo(int heightCount,int widthCount);

	void SetClip(const wstring& clipName, float speed, ANIMATION_TYPE type);
	void SetClipName(const wstring& clipName);
	void SetSpeed(float speed);
	void SetType(ANIMATION_TYPE type);
	void MakeClip(const wstring&  imgName, int sizeX, int sizeY);

public:
	bool PlayAnim(Renderer * render,Vertex* vertex);

private:
	int animStartX;
	int animStartY;
	int animEndX;
	int animEndY;
	float animTime;

	float animXGap;
	float animYGap;
	map<wstring, ANIM_INFO> m_Clips;
	
	wstring		m_ClipName;
	float		m_AnimSpeed;
	ANIMATION_TYPE m_AnimType;


};

