#include "jsSceneManager.h"
#include "jsTitleScene.h"
#include "jsPlayScene.h"

namespace js
{
	Scene* SceneManager::mScene[(UINT)eSceneType::End] = {};
	Scene* SceneManager::mCurScene = nullptr;
	
	void SceneManager::Initialize()
	{
		mScene[(UINT)eSceneType::Title] = new TitleScene;
		mScene[(UINT)eSceneType::Title]->Initialize();
		mScene[(UINT)eSceneType::Play] = new PlayScene;
		mScene[(UINT)eSceneType::Play]->Initialize();

		ChangeScene(eSceneType::Title);
	}

	void SceneManager::Tick()
	{
		mCurScene->Tick();
	}
	
	void SceneManager::Render(HDC _dc)
	{
		mCurScene->Render(_dc);
	}
	void SceneManager::Release()
	{
		for (Scene* scene : mScene)
		{
			if (nullptr != scene)
			{
				delete scene;
				scene = nullptr;
			}
		}
	}
	void SceneManager::ChangeScene(eSceneType type)
	{
		if (nullptr == mCurScene)
		{
			mCurScene = mScene[(UINT)eSceneType::Title];
		}
		else
		{
			mCurScene->Exit();
			mCurScene = mScene[(UINT)type];
		}
		mCurScene->Enter();
	}
}