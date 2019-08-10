#pragma once
#include "GameObject.h"
class Mouse :
	public GameObject
{
public:
	Mouse();
	virtual ~Mouse();

public:
	// CGameObject을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

public:
	void Move();

private:
	virtual void Release() override;
};

