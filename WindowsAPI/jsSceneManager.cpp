#include "jsSceneManager.h"
#include "jsLogoScene.h"

namespace js
{
	jsScene* jsSceneManager::m_Scene[(UINT)eSceneType::END] = {};
	jsScene* jsSceneManager::m_CurScene = nullptr;
	
	void jsSceneManager::Initialize()
	{
		m_Scene[(UINT)eSceneType::LOGO] = new jsLogoScene;
		m_Scene[(UINT)eSceneType::LOGO]->Initialize();

		m_CurScene = m_Scene[(UINT)eSceneType::LOGO];
	}

	void jsSceneManager::Tick()
	{
		m_CurScene->Tick();
	}
	
	void jsSceneManager::Render(HDC _dc)
	{
		m_CurScene->Render(_dc);
	}
	void jsSceneManager::Release()
	{
		for (jsScene* scene : m_Scene)
		{
			if (nullptr != scene)
			{
				delete scene;
				scene = nullptr;
			}
		}
	}
}