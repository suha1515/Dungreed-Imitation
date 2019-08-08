#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

void Weapon::Initialize()
{
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 68;
	
	m_Rotation.SetIdentity();
	m_Scale.SetIdentity();
	m_Translation.SetTranslation(m_tInfo.pos.x, m_tInfo.pos.y);

	GameObject::UpdateTex();
	GameObject::UpdateCopy();
}

int Weapon::Update()
{
	if (m_bIsDead)
		return DEAD_OBJ;
	
	Move();


	return 0;
}

void Weapon::Render(Renderer * render)
{
	render->SetVertexBuffer(m_tInfo.copy_vertex);
	render->SetTexture(ImageManager::GetInstance()->GetBitMap(L"Weapon_Spear"));
	render->DrawOnCanvas();
}

void Weapon::Move()
{
	m_Scale.SetScale(1.f);
	GameObject* mouse = *(ObjectManager::GetInstance()->GetObjectList(OBJECT_MOUSE).begin());
	Vector2 mousePos = mouse->GetInfo().pos;
	float angle = GetAngle(m_tInfo.pos, mousePos);
	//창 무기가.. 90도로이미 세워져있으므로.. 나중에 pivot이라는 변수를 넣어서 회전을 참고하자..
	angle -= 90.f;
	m_Rotation.SetRotation(angle);
	m_Translation.SetTranslation(m_tInfo.pos.x, m_tInfo.pos.y);

	Matrix3D transform = (m_Translation*m_Rotation*m_Scale);
	for (int i = 0; i < 4; ++i)
	{
		m_tInfo.copy_vertex[i].pos = transform*m_tInfo.vertex[i].pos;
	}
}

void Weapon::TrackPlayer()
{

}

void Weapon::Release()
{
}
