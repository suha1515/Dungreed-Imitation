#include "stdafx.h"
#include "SceneManager.h"
#include "Title.h"
#include "Edit.h"

IMPLEMENT_SINGLETON(SceneManager)
SceneManager::SceneManager():m_pCurrentScene(nullptr),m_ePreSceneType(SCENE_END),m_eCurSceneType(SCENE_END)
{
}


SceneManager::~SceneManager()
{
	Release();
}

void SceneManager::SceneChange(SCENE_NAME eSceneType)
{
	m_eCurSceneType = eSceneType;

	if (m_ePreSceneType != m_eCurSceneType)
	{
		SafeDelete(m_pCurrentScene);

		// State 패턴
		// FSM을 상속과 다형성으로 확장한 디자인 패턴.
		switch (m_eCurSceneType)
		{
		case SCENE_TITLE:
			m_pCurrentScene = new Title;
			break;
		case SCENE_MENU:
			
			break;
		case SCENE_EDIT:
			m_pCurrentScene = new Edit;
			break;
		case SCENE_STAGE:

			break;
		}

		m_pCurrentScene->Initialize();
		m_ePreSceneType = m_eCurSceneType;
	}
}

void SceneManager::Update()
{
	NULL_CHECK(m_pCurrentScene);
	m_pCurrentScene->Update();
}

void SceneManager::Render(Renderer* render)
{
	NULL_CHECK(m_pCurrentScene);
	m_pCurrentScene->Render(render);
}

void SceneManager::Release()
{
	SafeDelete(m_pCurrentScene);
}
