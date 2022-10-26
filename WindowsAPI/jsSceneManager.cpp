#include "jsSceneManager.h"
#include "jsLogoScene.h"

namespace js
{
	Scene* SceneManager::m_Scene[(UINT)eSceneType::End] = {};
	Scene* SceneManager::m_CurScene = nullptr;
	
	void SceneManager::Initialize()
	{
		m_Scene[(UINT)eSceneType::Logo] = new jsLogoScene;
		m_Scene[(UINT)eSceneType::Logo]->Initialize();

		m_CurScene = m_Scene[(UINT)eSceneType::Logo];
	}

	void SceneManager::Tick()
	{
		m_CurScene->Tick();
	}
	
	void SceneManager::Render(HDC _dc)
	{
		m_CurScene->Render(_dc);
	}
	void SceneManager::Release()
	{
		for (Scene* scene : m_Scene)
		{
			if (nullptr != scene)
			{
				delete scene;
				scene = nullptr;
			}
		}
	}
}