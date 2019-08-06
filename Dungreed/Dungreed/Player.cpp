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
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	GameObject::UpdateTex();
}

int Player::Update()
{
	return 0;
}

void Player::Render(Renderer* render)
{
	render->SetVertexBuffer(m_tInfo.texpos);
	render->SetTexture(ImageManager::GetInstance()->GetBitMap(L"wolf"));
	render->DrawOnCanvas();
}

void Player::Release()
{
}
