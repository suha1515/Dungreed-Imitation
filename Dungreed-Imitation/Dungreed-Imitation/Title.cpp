#include "stdafx.h"
#include "Title.h"


Title::Title()
{
}


Title::~Title()
{
}

void Title::Initialize()
{
	ImageManager::GetInstance()->LoadBitMap(L"../texture/Main/MainLogo.bmp", L"Title_Logo");
	ImageManager::GetInstance()->LoadBitMap(L"../texture/Main/DunGreedAnim.bmp", L"Title_Anim");

	m_Animator.Initialize();
	m_Animator.MakeClip(L"Title_Anim", 320, 71);
	m_Animator.SetClip(L"Title_Anim", 10.f, ANIMATION_LOOP);
}

int Title::Update()
{
	if (KeyManager::GetInstance()->KeyUp(KEY_RETURN))
	{
		SceneManager::GetInstance()->SceneChange(SCENE_EDIT);
		return 0;
	}
	return 0;
}

void Title::Render(Renderer* render)
{
	//render->DrawBitMap(250, 100, ImageManager::GetInstance()->GetBitMap(L"Title_Logo"));

	Vertex p1(Vector2(-200.f, 200.0f), Vector2(0.f, 0.f), mRGB(1.f, 0.f, 0.f));
	Vertex p2(Vector2(-200.f, 50.0f), Vector2(0.f, 1.f), mRGB(0.f, 1.f, 0.f));
	Vertex p3(Vector2(200.f, 50.0f), Vector2(1.f, 1.f), mRGB(0.f, 0.f, 1.f));
	Vertex p4(Vector2(200.f, 200.0f), Vector2(1.f, 0.f), mRGB(0.f, 0.f, 1.f));

	Vertex buffer[4];
	buffer[0] = p1;
	buffer[1] = p2;
	buffer[2] = p3;
	buffer[3] = p4;

	render->SetVertexBuffer(buffer);
	//m_Animator.PlayAnim(render, buffer);
	render->SetTexture(ImageManager::GetInstance()->GetBitMap(L"Title_Logo"));
	render->DrawOnCanvas();
	//DrawUtil::DrawGrid(BackDC, WINCX, WINCY, RGB(255, 0, 0));
}		  

void Title::Release()
{
}
