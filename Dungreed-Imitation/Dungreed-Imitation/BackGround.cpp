#include "stdafx.h"
#include "BackGround.h"


BackGround::BackGround()
{
}


BackGround::~BackGround()
{
}

void BackGround::Initialize()
{

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 32.f;

	m_Rotation.SetIdentity();
	m_Scale.SetIdentity();

	GameObject::UpdateTex();
	GameObject::UpdateCopy();
}

int BackGround::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;
	Move();

	return 0;
}

void BackGround::Render(Renderer * render)
{
	render->SetVertexBuffer(m_tInfo.copy_vertex);
	render->SetTexture(m_ObjectImg);
	render->DrawOnCanvas();
}

void BackGround::Move()
{
	m_Scale.SetScale(1.f);
	m_Translation.SetTranslation(m_tInfo.pos.x, m_tInfo.pos.y);

	Matrix3D transform = (m_Translation*m_Rotation*m_Scale);
	for (int i = 0; i < 4; ++i)
	{
		m_tInfo.copy_vertex[i].pos = transform*m_tInfo.vertex[i].pos;
	}
}

void BackGround::Release()
{
}
