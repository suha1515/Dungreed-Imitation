#pragma once
#include "GameObject.h"
class Player :
	public GameObject
{
public:
	Player();
	virtual ~Player();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

	private:
	virtual void Release() override;

};

