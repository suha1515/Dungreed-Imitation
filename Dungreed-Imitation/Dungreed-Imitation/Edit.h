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

private:
	virtual void Release() override;

private:
	void KeyInput();

	bool TileList = false;

	float tex_GapX;
	float tex_GapY;

	float startTileX;
	float startTileY;

	float EndTileX;
	float EndTileY;

	int widthBlock;
	int heightBlock;
};

