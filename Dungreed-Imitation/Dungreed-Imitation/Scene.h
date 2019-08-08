#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Render(Renderer *render) = 0;

protected:
	virtual void Release() = 0;
};

