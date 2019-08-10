#pragma once
#include "Item.h"
class Weapon :
	public Item
{
public:
	Weapon();
	~Weapon();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;
public:
	void Move();
	void TrackPlayer();
private:
	virtual void Release() override;

};

