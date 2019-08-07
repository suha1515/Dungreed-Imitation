#include "stdafx.h"
#include "Player.h"


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

	m_Animator.Initialize();
	m_Animator.MakeClip(L"IdleClip", 32, 32);

	GameObject::UpdateTex();
	GameObject::UpdateCopy();
	
}

int Player::Update()
{
	KeyInput();
	Move();
	//cout << m_tInfo.pos.x << " " << m_tInfo.pos.y << endl;
	//GameObject::UpdateTex();
	return 0;
}

void Player::Render(Renderer* render)
{	
	render->SetVertexBuffer(m_tInfo.copy_vertex);
	m_Animator.PlayAnim(render, L"IdleClip", m_tInfo.copy_vertex, ANIMATION_LOOP, 10.f);
	render->DrawOnCanvas();
}

void Player::KeyInput()
{
	if (KeyManager::GetInstance()->KeyPressing(KEY_LEFT))
	{
		m_tInfo.pos.x -= m_fSpeed*DELTA_TIME;
	}
	else if (KeyManager::GetInstance()->KeyPressing(KEY_RIGHT))
	{
		m_tInfo.pos.x += m_fSpeed*DELTA_TIME;

	}
	else if (KeyManager::GetInstance()->KeyPressing(KEY_UP))
	{
		m_tInfo.pos.y += m_fSpeed*DELTA_TIME;	
	}
	else if (KeyManager::GetInstance()->KeyPressing(KEY_DOWN))
	{
		m_tInfo.pos.y -= m_fSpeed*DELTA_TIME;
	}
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
