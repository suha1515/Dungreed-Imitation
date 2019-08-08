#pragma once
class Scene;
class SceneManager
{
	DECLARE_SINGLETON(SceneManager)
public:
	SceneManager();
	~SceneManager();


public:
	void SceneChange(SCENE_NAME eSceneType);
	void Update();
	void Render(Renderer* render);

private:
	void Release();

private:
	Scene*		m_pCurrentScene;
	SCENE_NAME	m_ePreSceneType;
	SCENE_NAME	m_eCurSceneType;
};

