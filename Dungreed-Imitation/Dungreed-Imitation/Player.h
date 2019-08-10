#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	enum STATE { IDLE, WALK, ATTACK, HIT, DEAD };
	enum Dir   {LEFT,RIGHT};
public:
	Player();
	virtual ~Player();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

public:
	void KeyInput();
	void AnimState();
	void FlipTex();
	void Move();

private:
	virtual void Release() override;

private:
	GameObject *m_Wpnlist[2];
	Vector2		m_WeaponPos[2];

	float		m_Angle;
	float		m_fSpeed;

	Animator	m_Animator;

	STATE		m_ePreState;
	STATE		m_eCurState;

	Dir			m_PreDir;
	Dir			m_CurDir;

	Vector2     m_LastPos;
	Vector2     m_CurPos;

};

