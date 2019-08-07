#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
#include "Mouse.h"


MainGame::MainGame()
{

}


MainGame::~MainGame()
{
	Release();
}

void MainGame::Initialize()
{
	//래스터라이저 및 렌더러 설정.
	//
	
	Vector2 origin(WINCX / 2.0f, WINCY / 2.0f);

	m_render.m_ScreenCoord.SetInfo(Vector2(1, 0), Vector2(0, -1), origin);
	m_render.SetRasterizer(g_hDC, WINCX, WINCY);
	m_render.SetColorMask(mRGB(1.f, 0.f, 1.f));

	//그림파일들
	ImageManager::GetInstance()->LoadBitMap(L"..//texture//1.bmp", L"wolf");
	ImageManager::GetInstance()->LoadBitMap(L"..//texture//1.bmp",L"Desk");
	ImageManager::GetInstance()->LoadBitMap(L"..//texture//800x600.bmp",L"배경");
	ImageManager::GetInstance()->LoadBitMap(L"..//texture//커서.bmp", L"마우스");
	ImageManager::GetInstance()->LoadBitMap(L"..//texture//캐릭터//Idle//wake//IdleClip.bmp", L"IdleClip");
	ImageManager::GetInstance()->LoadBitMap(L"..//texture//캐릭터//Idle//wake//Idle4.bmp", L"Idle4");

	GameObject* pGameObject = new Player;
	pGameObject->SetPos(Vector2(0.f, 0.f));
	pGameObject->Initialize();
	ObjectManager::GetInstance()->AddObject(OBJECT_PLAYER, pGameObject);

	pGameObject = new Mouse;
	pGameObject->SetPos(Vector2(40.f, 40.f));
	pGameObject->Initialize();
	ObjectManager::GetInstance()->AddObject(OBJECT_MOUSE, pGameObject);
}

void MainGame::Update()
{
	KeyManager::GetInstance()->Update();
	ObjectManager::GetInstance()->Update();
}

void MainGame::Render()
{
	m_render.ClearScreen();


	//Matrix2D rotation;

	//static float theta = 0.0f;
	//theta = theta + DELTA_TIME;

	//rotation.SetRotation(theta);

	Vertex p1(Vector2(200.f, 232.0f), Vector2(0.f, 0.f), mRGB(1.f, 0.f, 0.f));
	Vertex p2(Vector2(200.f, 200.0f), Vector2(0.f, 1.f), mRGB(0.f, 1.f, 0.f));
	Vertex p3(Vector2(232.f, 200.0f), Vector2(1.f, 1.f), mRGB(0.f, 0.f, 1.f));
	Vertex p4(Vector2(232.f, 232.0f), Vector2(1.f, 0.f), mRGB(0.f, 0.f, 1.f));

	Vertex buffer[4];
	buffer[0] = p1;
	buffer[1] = p2;
	buffer[2] = p3;
	buffer[3] = p4;

	m_render.SetVertexBuffer(buffer);
	m_render.SetTexture(ImageManager::GetInstance()->GetBitMap(L"Idle4"));
	m_render.DrawOnCanvas();


	//Vertex a1 = p1;
	//Vertex a2 = p2;
	//Vertex a3 = p3;
	//Vertex a4 = p4;

	//a1.pos = a1.pos*rotation;
	//a2.pos = a2.pos*rotation;
	//a3.pos = a3.pos*rotation;
	//a4.pos = a4.pos*rotation;

	//m_render.DrawTriangleBarycentric(p1, p2, p3);
	//render.DrawTriangleBarycentric(a1, a2, a3, &bitmap);
	//render.DrawTriangleBarycentric(a3, a4, a1, &bitmap);

	//200마리시 Debug 는 2로.. Release는 49로..
	/*for (int i = 0; i < 20; ++i)
	{
	int b = 10 * i + 10;
	for (int j = 0; j < 10; ++j)
	{
	int a = 10 * j + 10;
	Vertex a1 = Vertex(p1.pos+Vector2(b,a),p1.tex,p1.color);
	Vertex a2 = Vertex(p2.pos + Vector2(b, a), p2.tex, p2.color);
	Vertex a3 = Vertex(p3.pos + Vector2(b, a), p3.tex, p3.color);
	Vertex a4 = Vertex(p4.pos + Vector2(b, a), p4.tex, p4.color);

	render.DrawTriangleBarycentric(a1, a2, a3, &bitmap);
	render.DrawTriangleBarycentric(a3, a4, a1, &bitmap);

	}
	}*/

	//render.DrawTriangleBarycentric(p1, p2, p3, g_image);
	//render.DrawTriangleBarycentric(p3, p4, p1, g_image);

	ObjectManager::GetInstance()->Render(&m_render);
	m_render.Present(&g_hDC);
	//
}

void MainGame::SetRenderer(Renderer* _render)
{

}

void MainGame::Release()
{
	ObjectManager::GetInstance()->DestroyInstance();
	ImageManager::GetInstance()->DestroyInstance();
	KeyManager::GetInstance()->DestroyInstance();
}
