#pragma once
#include "GameObject.h"
class BackGround :
	public GameObject
{
public:
	BackGround();
	~BackGround();

public:
	// GameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

public:
	void Move();

private:
	virtual void Release() override;
};

