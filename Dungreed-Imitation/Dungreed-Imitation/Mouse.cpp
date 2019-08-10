#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
	Release();
}

void Mouse::Initialize()
{
	m_tInfo.fCX = 21.f;
	m_tInfo.fCY = 21.f;

	m_Rotation.SetIdentity();
	m_Scale.SetIdentity();

	SetImage(ImageManager::GetInstance()->GetBitMap(L"마우스"));
	GameObject::UpdateTex();
	GameObject::UpdateCopy();
}

int Mouse::Update()
{
	Move();
	return NO_EVENT;
}

void Mouse::Render(Renderer* render)
{
	render->SetVertexBuffer(m_tInfo.copy_vertex);
	render->SetTexture(m_ObjectImg);
	//Ellipse(g_hDC, m_tInfo.pos.x - m_tInfo.fCX*0.5f, m_tInfo.pos.y - m_tInfo.fCY*0.5f, m_tInfo.pos.x + m_tInfo.fCX*0.5f, m_tInfo.pos.y + m_tInfo.fCY*0.5f);
	render->DrawOnCanvas();
}

void Mouse::Move()
{
	POINT pt = {};

	//현재 마우스 커서 위치를 얻어오는 API 함수
	//클라이언트 상의 좌표가 아닌 전체 스크린 좌표 상의 마우스 커서 위치를 얻어옴.
	GetCursorPos(&pt);

	//스크린 좌표로 얻어온 마우스 위치를 클라이언트 좌표로 변환하는 API 함수.
	ScreenToClient(g_hWnd, &pt);

	m_tInfo.pos.x = float(pt.x) - WINCX/2.0f;
	m_tInfo.pos.y = -(float(pt.y) - WINCY/2.0f);
	m_Translation.SetTranslation(m_tInfo.pos.x, m_tInfo.pos.y);
	Matrix3D transform = (m_Translation*m_Rotation*m_Scale);
	for (int i = 0; i < 4; ++i)
	{
		m_tInfo.copy_vertex[i].pos = transform*m_tInfo.vertex[i].pos;
	}
}

void Mouse::Release()
{
}
