#include "jsSceneManager.h"
#include "jsTitleScene.h"
#include "jsPlayScene.h"
#include "jsMapToolScene.h"
#include "jsTestScene.h"
#include "jsSelectScene.h"
#include "jsObject.h"

namespace js
{
	Scene* SceneManager::mScene[(UINT)eSceneType::End] = {};
	Scene* SceneManager::mPlayScene = nullptr;
	eSceneType SceneManager::mType = eSceneType::End;
	void SceneManager::Initialize()
	{
		mScene[(UINT)eSceneType::MapTool] = new MapToolScene();
		mScene[(UINT)eSceneType::MapTool]->Initialize();
		mScene[(UINT)eSceneType::Test] = new TestScene();
		mScene[(UINT)eSceneType::Test]->Initialize();
		mScene[(UINT)eSceneType::Title] = new TitleScene();
		mScene[(UINT)eSceneType::Title]->Initialize();
		mScene[(UINT)eSceneType::Select] = new SelectScene();
		mScene[(UINT)eSceneType::Select]->Initialize();
		mScene[(UINT)eSceneType::Play] = new PlayScene();
		mScene[(UINT)eSceneType::Play]->Initialize();
		ChangeScene(eSceneType::MapTool);
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