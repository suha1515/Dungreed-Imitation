#pragma once
#include "GameObject.h"
class BackGround :
	public GameObject
{
public:
	BackGround();
	~BackGround();

public:
	// GameObject��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Render(Renderer* render) override;

public:
	void Move();

private:
	virtual void Release() override;
};

