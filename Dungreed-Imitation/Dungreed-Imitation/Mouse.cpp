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

	SetImage(ImageManager::GetInstance()->GetBitMap(L"���콺"));
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

	//���� ���콺 Ŀ�� ��ġ�� ������ API �Լ�
	//Ŭ���̾�Ʈ ���� ��ǥ�� �ƴ� ��ü ��ũ�� ��ǥ ���� ���콺 Ŀ�� ��ġ�� ����.
	GetCursorPos(&pt);

	//��ũ�� ��ǥ�� ���� ���콺 ��ġ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ�ϴ� API �Լ�.
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
