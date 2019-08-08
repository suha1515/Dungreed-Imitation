#pragma once
#include "GameObject.h"
class Item :
	public GameObject
{
public:
	Item();
	~Item();
public:
	virtual void Initialize()=0;
	virtual int Update()=0;
	virtual void Render(Renderer* render)=0;

public:
	void SetItemType(ITEM_TYPE type);
private:
	virtual void Release()=0;

protected:
	ITEM_TYPE	m_ItemType;
};

