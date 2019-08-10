#include "stdafx.h"
#include "Edit.h"
#include "Mouse.h"
#include "BackGround.h"


Edit::Edit()
{
}


Edit::~Edit()
{
}

void Edit::Initialize()
{
	ImageManager::GetInstance()->LoadBitMap(L"../texture/Tile/MapTile1.bmp", L"Map_Tile1");
	m_curTilePallet = ImageManager::GetInstance()->GetBitMap(L"Map_Tile1");
	//Edit Mouse
	m_Mouse = new Mouse;
	m_Mouse->SetPos(Vector2(0.0f, 0.0f));
	m_Mouse->Initialize();
	ObjectManager::GetInstance()->AddObject(OBJECT_MOUSE, m_Mouse);


	//마우스의 기존 커서 정보를 받아둔다..
	m_PrevMouseImg = m_Mouse->GetImage();
	m_PrevMouseTex[0] = m_Mouse->GetInfo().vertex[0].tex;
	m_PrevMouseTex[1] = m_Mouse->GetInfo().vertex[1].tex;
	m_PrevMouseTex[2] = m_Mouse->GetInfo().vertex[2].tex;
	m_PrevMouseTex[3] = m_Mouse->GetInfo().vertex[3].tex;
	m_PrevMouseFCX = m_Mouse->GetInfo().fCX;
	m_PrevMouseFCY = m_Mouse->GetInfo().fCY;

	widthBlock = 8;
	heightBlock = 8;

	tex_GapX = (1.f / 32.f);
	tex_GapY = (1.f / 32.f);
	startTileX = 0;
	startTileY = 0;



}

int Edit::Update()
{
	KeyInput();
	GetMousePos();
	
	ObjectManager::GetInstance()->Update();
	return 0;
}

void Edit::Render(Renderer * render)
{
	if (b_TileList)
	{
		DrawUtil::DrawGrid(BackDC, WINCX / 16, WINCY / 16, RGB(255, 0, 0));
		if(b_Pallet)
		OpenPallet(render);
	}
	ObjectManager::GetInstance()->Render(render);
}

void Edit::OpenPallet(Renderer * render)
{
	/*
	tex_GapX , tex_GapY
	tex_GapX , tex_GapY*tileStart
	tex_GapX*tileStart,tex_GapY*tilestart
	tex_GapX*tileStart,tex_GapY
	
	 *widthBlock
	*heightBlock
	*/

	Vertex p1(Vector2(112.f, 204.0f), Vector2(0.f, 0.f), mRGB(1.f, 0.f, 0.f));
	Vertex p2(Vector2(112.f, -52.0f), Vector2(0.f, 1.f), mRGB(0.f, 1.f, 0.f));
	Vertex p3(Vector2(368.f, -52.0f), Vector2(1.f, 1.f), mRGB(0.f, 0.f, 1.f));
	Vertex p4(Vector2(368.f, 204.0f), Vector2(1.f, 0.f), mRGB(0.f, 0.f, 1.f));

	p1.tex = Vector2(0.0f,        0.0f)							+ Vector2(tex_GapX*widthBlock*startTileX, tex_GapY*heightBlock*startTileY);
	p2.tex = Vector2(0.f, tex_GapY*heightBlock)				    + Vector2(tex_GapX*widthBlock*startTileX, tex_GapY*heightBlock*startTileY);
	p3.tex = Vector2(tex_GapX*widthBlock,tex_GapY*heightBlock)  + Vector2(tex_GapX*widthBlock*startTileX, tex_GapY*heightBlock*startTileY);
	p4.tex = Vector2(tex_GapX*widthBlock,     0.f)				+ Vector2(tex_GapX*widthBlock*startTileX, tex_GapY*heightBlock*startTileY);

	Vertex buffer[4];
	buffer[0] = p1;
	buffer[1] = p2;
	buffer[2] = p3;
	buffer[3] = p4;

	render->SetVertexBuffer(buffer);
	render->SetTexture(m_curTilePallet);
	render->DrawOnCanvas();
	DrawUtil::DrawGrid(BackDC, 512, 96, 768, 352, 8, 8, RGB(0, 255, 0));
}

void Edit::GetMousePos()
{
	m_MousePos = m_Mouse->GetInfo().pos;
}

void Edit::IsClick()
{
	int mousePosx = m_MousePos.x + ORIGINX;
	int mousePosy = -m_MousePos.y + ORIGINY;

	//마우스 좌표는 윈도영역을 벗어날 수 없다.
	mousePosx = __max(0, __min(WINCX, mousePosx));
	mousePosy = __max(0, __min(WINCY, mousePosy));

	
	if (b_TileList)
	{
		//파레트가 켜진경우
		if (b_Pallet)
		{
			//팔레트 범위인 경우
			if ((512 <= mousePosx && 768 >= mousePosx) && (96 <= mousePosy && 352 >= mousePosy))
			{
				//x,y
				//인덱스 0			1				2			3	
				//0-31 1번째 칸 , 32-63 2번째 가로칸 64-95 3번째 96-127 4번째  
				int indexTileX = ((mousePosx - 512) / 32) + widthBlock*startTileX;
				int indexTileY = ((mousePosy - 96) / 32) + heightBlock*startTileY;

				float texPosx = tex_GapX * indexTileX;
				float texPosy = tex_GapY * indexTileY;
				
				//해당 타일에에 대한  전체 비트맵중 텍스쳐의 상대 좌표를 구한다.
				m_CurTexPos[0] = Vector2(0.0f, 0.0f) + Vector2(texPosx, texPosy);
				m_CurTexPos[1] = Vector2(0.f, tex_GapY) + Vector2(texPosx, texPosy);
				m_CurTexPos[2] = Vector2(tex_GapX, tex_GapY) + Vector2(texPosx, texPosy);
				m_CurTexPos[3] = Vector2(tex_GapX, 0.f) + Vector2(texPosx, texPosy);

				m_Mouse->SetImage(m_curTilePallet);
				m_Mouse->SetTexture(m_CurTexPos);
				m_Mouse->SetRatio(32, 32);
				//마우스에 타일이 올라간 상태
				b_ClickedTex = true;
				//cout << "가로 " << indexTileX+1 << " 칸 세로 " << indexTileY+1 << "칸" << endl;
				//cout << "텍스쳐 좌상단 좌표 : (" << texPos[0].x << " , " << texPos[0].y << ")" << endl;
				//cout << "텍스쳐 좌하단 좌표 : (" << texPos[1].x << " , " << texPos[1].y << ")" << endl;
				//cout << "텍스쳐 우하단 좌표 : (" << texPos[2].x << " , " << texPos[2].y << ")" << endl;
				//cout << "텍스쳐 우상단 좌표 : (" << texPos[3].x << " , " << texPos[3].y << ")" << endl;
			}
			//켜진 상태에서 맵클릭시 (파레트 범위는 그리지 않는다.
			else
			{
				int indexTileX = ((mousePosx ) / 32) ;
				int indexTileY = ((mousePosy ) / 32) ;
				cout << "맵가로 " << indexTileX+1 << " 칸 맵세로 " << indexTileY+1 << "칸" << endl;
				int tileLocX = indexTileX * 32 + 16;
				int tileLocY = indexTileY * 32 + 16;
				cout << "중점 위치 " << tileLocX << " 중점 위치 " << tileLocY << endl;
				//파레트에서 타일을 클릭했을경우
				if (b_ClickedTex)
				{
					InsertTile(tileLocX,tileLocY);
				}
			}
		}	
		//맵클릭시 파레트는 사라진 상태이므로 파레트 공간에도 그릴수있다.
		else
		{
			int indexTileX = ((mousePosx) / 32);
			int indexTileY = ((mousePosy) / 32);
			cout << "맵가로 " << indexTileX + 1 << " 칸 맵세로 " << indexTileY + 1 << "칸" << endl;
		}
	}
}

void Edit::InsertTile(int posX,int posY)
{
	// 타일이 찍힐 좌표를 스크린 좌표계 기준으로 지정
	Vector2 tilePos = Vector2((posX - ORIGINX), -(posY - ORIGINY)); 
	cout << tilePos.x << " , " << tilePos.y << endl;
	//현재 백그라운드에 찍힌 타일중 좌표가 겹히는지 find로 확인
	list<GameObject*>& backGround = ObjectManager::GetInstance()->GetObjectList(OBJECT_BACKGROUND);
	list<GameObject*>::iterator iter_find = find_if(backGround.begin(), backGround.end(),
		[&tilePos](GameObject* backTile) {
		Vector2 pos = backTile->GetInfo().pos;
		if (pos == tilePos)
		{
			return true;
		}
		return false;
	});
	//겹치지 않으면 새로운 타일을 만든다.
	if (iter_find == backGround.end())
	{
		cout << "타일 생성!" << endl;
		GameObject* pGameObject = new BackGround;
		pGameObject->SetPos(tilePos);
		pGameObject->Initialize();
		pGameObject->SetImage(m_curTilePallet);
		pGameObject->SetRatio(32, 32);
		pGameObject->SetTexture(m_CurTexPos);
		ObjectManager::GetInstance()->AddObject(OBJECT_BACKGROUND,pGameObject);
	}
	else	//겹치면 텍스쳐 자료만 바꾼다.
	{
		cout << "타일 바꾸기!" << endl;
		(*iter_find)->SetTexture(m_CurTexPos);
	}
}

void Edit::Release()
{
	//ObjectManager::GetInstance()->DestroyInstance();
}

void Edit::KeyInput()
{
	//수정 모드 키기
	if (KeyManager::GetInstance()->KeyUp(KEY_A))
	{
		if (!b_TileList)
		{
			b_TileList = true;
		}
		else
		{
			b_TileList = false;
		}
	}

	if (KeyManager::GetInstance()->KeyUp(KEY_P))
	{
		if (b_TileList)
		{
			if (!b_Pallet)
				b_Pallet = true;
			else
				b_Pallet = false;
		}
	}

	//팔레트 상하좌우로 옮기기
	if (KeyManager::GetInstance()->KeyUp(KEY_RIGHT))
	{
		if (b_TileList)
		{
			startTileX += 1;
		}
	}
	if (KeyManager::GetInstance()->KeyUp(KEY_LEFT))
	{
		if (b_TileList)
		{
			startTileX -= 1;
		}
	}
	if (KeyManager::GetInstance()->KeyUp(KEY_UP))
	{
		if (b_TileList)
		{
			startTileY -= 1;
		}
	}
	if (KeyManager::GetInstance()->KeyUp(KEY_DOWN))
	{
		if (b_TileList)
		{
			startTileY += 1;
		}
	}

	if (KeyManager::GetInstance()->KeyUp(KEY_LBUTTON))
	{
			IsClick();	
	}
	if (KeyManager::GetInstance()->KeyUp(KEY_RBUTTON))
	{
		if (b_TileList)
		{
			m_Mouse->SetImage(m_PrevMouseImg);
			m_Mouse->SetRatio(m_PrevMouseFCX, m_PrevMouseFCY);
			m_Mouse->SetTexture(m_PrevMouseTex);
			b_ClickedTex = false;
		}
	}
	
	startTileX = __max(0, __min(3, startTileX));
	startTileY = __max(0, __min(3, startTileY));
}
