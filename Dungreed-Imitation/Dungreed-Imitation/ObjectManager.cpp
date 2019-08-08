#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(ObjectManager)
ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	Release();
}

void ObjectManager::AddObject(OBJECT_TYPE type, GameObject * pObject)
{
	NULL_CHECK(pObject);
	m_ObjLst[type].push_back(pObject);
}

void ObjectManager::Update()
{
	m_iEvent = NO_EVENT;

	for (int i = 0; i < OBJECT_END; ++i)
	{
		list<GameObject*>::iterator iter_Begin = m_ObjLst[i].begin();
		list<GameObject*>::iterator iter_End = m_ObjLst[i].end();

		for (; iter_Begin != iter_End; )
		{
			m_iEvent = (*iter_Begin)->Update();

			if (DEAD_OBJ == m_iEvent)
			{
				SafeDelete(*iter_Begin);
				iter_Begin = m_ObjLst[i].erase(iter_Begin);
			}
			/*else if (CHANGE_SCENE == m_iEvent)
			return;*/
			else
				++iter_Begin;
		}
	}
}

void ObjectManager::Render(Renderer* render)
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for (auto& pObject : m_ObjLst[i])
			pObject->Render(render);
	}
}

void ObjectManager::ReleaseGroup(OBJECT_TYPE type)
{
}

list<GameObject*>& ObjectManager::GetObjectList(OBJECT_TYPE type)
{
	return m_ObjLst[type];
}

void ObjectManager::Release()
{
	for (int i = 0; i < OBJECT_END; ++i)
	{
		for_each(m_ObjLst[i].begin(), m_ObjLst[i].end(), SafeDelete<GameObject*>);
		m_ObjLst[i].clear();
	}
}
