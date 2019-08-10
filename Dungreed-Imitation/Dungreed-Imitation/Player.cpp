#include "stdafx.h"
#include "Player.h"
#include "Weapon.h"


Player::Player()
{

}


Player::~Player()
{
}

void Player::Initialize()
{
	m_tInfo.fCX = 64;
	m_tInfo.fCY = 64;
	m_Angle = 0.0f;
	m_fSpeed    = 300.f;

	// 회전,스케일,이동행렬 초기화.
	// 이동행렬은 생성시 위치로 지정.
	m_Rotation.SetIdentity();
	m_Scale.SetIdentity();
	m_Translation.SetTranslation(m_tInfo.pos.x, m_tInfo.pos.y);

	//애니메이션 클립및 상태 설정-------
	m_Animator.Initialize();
	m_Animator.MakeClip(L"IdleClip", 32, 32);
	m_Animator.MakeClip(L"runClip", 32, 32);
	m_Animator.SetClip(L"IdleClip", 10.f, ANIMATION_LOOP);

	m_eCurState = IDLE;
	m_ePreState = m_eCurState;

	m_CurDir = LEFT;
	m_PreDir = RIGHT;
	//----------------------------------
	m_LastPos = m_tInfo.pos;
	m_CurPos = m_tInfo.pos;

	//무기 상태 설정
	m_WeaponPos[LEFT] = Vector2(m_tInfo.pos.x - 5, m_tInfo.pos.y - 5);
	m_WeaponPos[RIGHT] = Vector2(m_tInfo.pos.x + 5, m_tInfo.pos.y - 5);

	m_Wpnlist[0] = nullptr;
	m_Wpnlist[1] = nullptr;

	m_Wpnlist[0] = new Weapon;
	m_Wpnlist[0]->SetPos(m_tInfo.pos);
	m_Wpnlist[0]->Initialize();
	ObjectManager::GetInstance()->AddObject(OBJECT_ITEM,m_Wpnlist[0]);

	GameObject::UpdateTex();
	GameObject::UpdateCopy();
	
}

int Player::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;
	KeyInput();
	FlipTex();
	AnimState();
	Move();
	
	m_WeaponPos[LEFT] = Vector2(m_tInfo.pos.x - 5, m_tInfo.pos.y - 10);
	m_WeaponPos[RIGHT] = Vector2(m_tInfo.pos.x + 5, m_tInfo.pos.y - 10);

	m_Wpnlist[0]->SetPos(m_WeaponPos[m_CurDir]);
	return NO_EVENT;
}

void Player::Render(Renderer* render)
{	
	render->SetVertexBuffer(m_tInfo.copy_vertex);
	m_Animator.PlayAnim(render, m_tInfo.copy_vertex);
	render->DrawOnCanvas();
}

void Player::KeyInput()
{
	if (KeyManager::GetInstance()->KeyPressing(KEY_LEFT))
	{
		m_tInfo.pos.x -= m_fSpeed*DELTA_TIME;
		m_CurPos = m_tInfo.pos;
		m_eCurState = WALK;
	}
	else if (KeyManager::GetInstance()->KeyPressing(KEY_RIGHT))
	{
		m_tInfo.pos.x += m_fSpeed*DELTA_TIME;
		m_CurPos = m_tInfo.pos;
		m_eCurState = WALK;
	}
	else if (KeyManager::GetInstance()->KeyPressing(KEY_UP))
	{
		m_tInfo.pos.y += m_fSpeed*DELTA_TIME;
		m_CurPos = m_tInfo.pos;
	}
	else if (KeyManager::GetInstance()->KeyPressing(KEY_DOWN))
	{
		m_tInfo.pos.y -= m_fSpeed*DELTA_TIME;
		m_CurPos = m_tInfo.pos;
	}
	else
		m_eCurState = IDLE;

}

void Player::AnimState()
{
	if (m_ePreState != m_eCurState)
	{
		// FSM (Finite State Machine, 유한 상태 기계)
		// 기계는 오로지 하나의 동작만 취한다.
		switch (m_eCurState)
		{
		case IDLE:
			m_Animator.SetClip(L"IdleClip", 10.f, ANIMATION_LOOP);
			break;
		case WALK:
			m_Animator.SetClip(L"runClip", 5.f, ANIMATION_LOOP);
			break;
		case ATTACK:
			break;
		case HIT:
			break;
		case DEAD:
			break;
		}

		m_ePreState = m_eCurState;
	}
}

void Player::FlipTex()
{
	if (m_CurPos.x < m_LastPos.x)
	{
		m_CurDir = LEFT;
	}
	else if(m_CurPos.x > m_LastPos.x)
	{
		m_CurDir = RIGHT;
	}
	if (m_CurDir != m_PreDir)
	{
		Flip();
		m_Wpnlist[0]->Flip();
		m_PreDir = m_CurDir;
	}
	m_LastPos = m_CurPos;
}

void Player::Move()
{
	//m_angle = m_angle + DELTA_TIME * 5.f;
	//m_Rotation.SetRotation(m_angle);
	m_Scale.SetScale(1.f);
	m_Translation.SetTranslation(m_tInfo.pos.x, m_tInfo.pos.y);

	Matrix3D transform = (m_Translation*m_Rotation*m_Scale);
	for (int i = 0; i < 4; ++i)
	{
		m_tInfo.copy_vertex[i].pos = transform*m_tInfo.vertex[i].pos;
	}
	//m_tInfo.pos = m_tInfo.pos *rotation;
}

void Player::Release()
{
}
