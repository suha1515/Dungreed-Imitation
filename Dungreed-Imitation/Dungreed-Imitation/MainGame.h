#pragma once
class GameObject;
class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void Initialize();
	void Update();
	void Render();
	void SetRenderer(Renderer* render);

private:
	void Release();

private:
	Renderer    m_render;
};

