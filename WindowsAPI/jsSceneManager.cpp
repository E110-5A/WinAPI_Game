#include "jsSceneManager.h"
#include "jsTitleScene.h"
#include "jsPlayScene.h"
#include "jsToolScene.h"
#include "jsObject.h"

namespace js
{
	Scene* SceneManager::mScene[(UINT)eSceneType::End] = {};
	Scene* SceneManager::mPlayScene = nullptr;
	eSceneType SceneManager::mType = eSceneType::End;
	void SceneManager::Initialize()
	{
		mScene[(UINT)eSceneType::Title] = new TitleScene;
		mScene[(UINT)eSceneType::Title]->Initialize();
		mScene[(UINT)eSceneType::Play] = new PlayScene;
		mScene[(UINT)eSceneType::Play]->Initialize();
		mScene[(UINT)eSceneType::Tool] = new ToolScene;
		mScene[(UINT)eSceneType::Tool]->Initialize();
		ChangeScene(eSceneType::Play);
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}
	
	void SceneManager::Render(HDC _dc)
	{
		mPlayScene->Render(_dc);
	}
	void SceneManager::DestroyGameObject()
	{
		object::Release();
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
		if (nullptr == mPlayScene)
			return;
		mType = type;

		mPlayScene->Exit();
		mPlayScene = mScene[(UINT)type];

		mPlayScene->Enter();
	}
}