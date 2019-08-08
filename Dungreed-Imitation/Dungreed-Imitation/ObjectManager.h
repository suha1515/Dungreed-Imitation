#pragma once
class GameObject;
class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager)
public:
	ObjectManager();
	~ObjectManager();

public:
	void AddObject(OBJECT_TYPE type, GameObject* pObject);
	void Update();
	void Render(Renderer* render);
	void ReleaseGroup(OBJECT_TYPE type);

	list<GameObject*>& GetObjectList(OBJECT_TYPE type);

private:
	void Release();

private:
	list<GameObject*> m_ObjLst[OBJECT_END];
	int				  m_iEvent;
};

