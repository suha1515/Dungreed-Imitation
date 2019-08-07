#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

public:
	void KeyInput();
	void Move();

private:
	virtual void Release() override;

private:
	float		m_Angle;
	float		m_fSpeed;
	Animator	m_Animator;

};

