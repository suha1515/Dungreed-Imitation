#pragma once
#include "Scene.h"
class Edit :
	public Scene
{
public:
	Edit();
	~Edit();

public:
	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;
public:
	void OpenPallet(Renderer * render);

public:
	void GetMousePos();
	void IsClick();
	void InsertTile(int posX, int posY);

private:
	virtual void Release() override;

private:
	void KeyInput();

	bool b_TileList = false;
	bool b_Pallet = false;
	bool b_ClickedTex = false;

	float tex_GapX;
	float tex_GapY;

	float startTileX;
	float startTileY;

	float EndTileX;
	float EndTileY;

	int widthBlock;
	int heightBlock;

	Vector2 m_MousePos;
	Vector2 m_CurTexPos[4];
	GameObject* m_Mouse;
	

	BitMap*		m_PrevMouseImg;
	Vector2     m_PrevMouseTex[4];
	float		m_PrevMouseFCX, m_PrevMouseFCY;


	BitMap*		m_curTilePallet;

};

