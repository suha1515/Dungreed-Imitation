#include "stdafx.h"
#include "Edit.h"


Edit::Edit()
{
}


Edit::~Edit()
{
}

void Edit::Initialize()
{
	ImageManager::GetInstance()->LoadBitMap(L"../texture/Tile/MapTile1.bmp", L"Map_Tile1");

	widthBlock = 6;
	heightBlock = 12;

	tex_GapX = (1.f / 32.f)*widthBlock;
	tex_GapY = (1.f / 32.f)*heightBlock;
	startTileX = 0;
	startTileY = 0;



}

int Edit::Update()
{
	KeyInput();
	return 0;
}

void Edit::Render(Renderer * render)
{
	if (TileList)
	{
		DrawUtil::DrawGrid(BackDC, WINCX / 16, WINCY / 16, RGB(255, 0, 0));
		OpenPallet(render);
	}

	
	
}

void Edit::OpenPallet(Renderer * render)
{
	/*
	tex_GapX , tex_GapY
	tex_GapX , tex_GapY*tileStart
	tex_GapX*tileStart,tex_GapY*tilestart
	tex_GapX*tileStart,tex_GapY
	
	
	*/

	Vertex p1(Vector2(176.f, 236.0f), Vector2(0.f, 0.f), mRGB(1.f, 0.f, 0.f));
	Vertex p2(Vector2(176.f, -148.0f), Vector2(0.f, 1.f), mRGB(0.f, 1.f, 0.f));
	Vertex p3(Vector2(368.f, -148.0f), Vector2(1.f, 1.f), mRGB(0.f, 0.f, 1.f));
	Vertex p4(Vector2(368.f, 236.0f), Vector2(1.f, 0.f), mRGB(0.f, 0.f, 1.f));

	p1.tex = Vector2(0.0f,        0.0f)  + Vector2(tex_GapX*startTileX, tex_GapY*startTileY);
	p2.tex = Vector2(0.f,     tex_GapY)  + Vector2(tex_GapX*startTileX, tex_GapY*startTileY);
	p3.tex = Vector2(tex_GapX,tex_GapY)  + Vector2(tex_GapX*startTileX, tex_GapY*startTileY);
	p4.tex = Vector2(tex_GapX,     0.f)  + Vector2(tex_GapX*startTileX, tex_GapY*startTileY);

	Vertex buffer[4];
	buffer[0] = p1;
	buffer[1] = p2;
	buffer[2] = p3;
	buffer[3] = p4;

	render->SetVertexBuffer(buffer);
	render->SetTexture(ImageManager::GetInstance()->GetBitMap(L"Map_Tile1"));
	render->DrawOnCanvas();
	DrawUtil::DrawGrid(BackDC, 576, 64, 768, 448, 12, 6, RGB(0, 255, 0));
}

void Edit::Release()
{
}

void Edit::KeyInput()
{
	if (KeyManager::GetInstance()->KeyUp(KEY_A))
	{
		if (!TileList)
		{
			TileList = true;
		}
		else
		{
			TileList = false;
		}
	}
	if (KeyManager::GetInstance()->KeyUp(KEY_RIGHT))
	{
		if (TileList)
		{
			startTileX += 1;
		}
	}
}
