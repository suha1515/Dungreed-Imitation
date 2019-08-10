#pragma once
#include "Scene.h"
class Title :
	public Scene
{
public:
	Title();
	~Title();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

private:
	virtual void Release() override;

	Animator m_Animator;
};

