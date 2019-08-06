#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject():m_bIsDead(false)
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

void GameObject::SetPos(CVector2 pos)
{
	m_tInfo.pos = pos;
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
	m_tInfo.texpos[0].pos = CVector2(m_tInfo.pos.x - m_tInfo.fCX*0.5f,m_tInfo.pos.y + m_tInfo.fCY*0.5f);
	m_tInfo.texpos[1].pos = CVector2(m_tInfo.pos.x - m_tInfo.fCX*0.5f, m_tInfo.pos.y - m_tInfo.fCY*0.5f);
	m_tInfo.texpos[2].pos = CVector2(m_tInfo.pos.x + m_tInfo.fCX*0.5f, m_tInfo.pos.y - m_tInfo.fCY*0.5f);
	m_tInfo.texpos[3].pos = CVector2(m_tInfo.pos.x + m_tInfo.fCX*0.5f, m_tInfo.pos.y + m_tInfo.fCY*0.5f);
}
