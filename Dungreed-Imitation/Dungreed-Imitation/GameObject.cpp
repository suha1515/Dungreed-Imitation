#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() :m_bIsDead(false)
{

}
GameObject::~GameObject()
{

}

const INFO & GameObject::GetInfo() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tInfo;
}

const RECT & GameObject::GetRect() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_tRect;
}

void GameObject::SetPos(Vector2 pos)
{
	m_tInfo.pos = pos;
}

void GameObject::SetRotation(float angle)
{
	m_Rotation.SetRotation(angle);
}

void GameObject::SetScale(float scale)
{
	m_Scale.SetScale(scale);
}

void GameObject::SetDead(bool IsDead)
{
	m_bIsDead = IsDead;
}

void GameObject::SetBmpKey(const wstring & wstKey)
{
	m_BmpName = wstKey;
}

void GameObject::UpdateTex()
{
	m_tInfo.vertex[0].pos = Vector2(-m_tInfo.fCX*0.5f , m_tInfo.fCY*0.5f);
	m_tInfo.vertex[1].pos = Vector2(-m_tInfo.fCX*0.5f , - m_tInfo.fCY*0.5f);
	m_tInfo.vertex[2].pos = Vector2(+ m_tInfo.fCX*0.5f, - m_tInfo.fCY*0.5f);
	m_tInfo.vertex[3].pos = Vector2(+ m_tInfo.fCX*0.5f,+ m_tInfo.fCY*0.5f);

	m_tInfo.vertex[0].tex = Vector2(0.f, 0.f);
	m_tInfo.vertex[1].tex = Vector2(0.f, 1.f);
	m_tInfo.vertex[2].tex = Vector2(1.f, 1.f);
	m_tInfo.vertex[3].tex = Vector2(1.f, 0.f);
}

void GameObject::UpdateCopy()
{
	for (int i = 0; i < 4; ++i)
	{
		m_tInfo.copy_vertex[i] = m_tInfo.vertex[i];
	}
}
