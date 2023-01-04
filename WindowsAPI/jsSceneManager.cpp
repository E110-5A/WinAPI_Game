#include "jsSceneManager.h"
#include "jsTitleScene.h"
#include "jsStageA.h"
#include "jsStageB.h"
#include "jsMapToolScene.h"
#include "jsTestScene.h"
#include "jsTestScene2.h"
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
		mScene[(UINT)eSceneType::Test2] = new TestScene2();
		mScene[(UINT)eSceneType::Test2]->Initialize();
		mScene[(UINT)eSceneType::Title] = new TitleScene();
		mScene[(UINT)eSceneType::Title]->Initialize();
		mScene[(UINT)eSceneType::Select] = new SelectScene();
		mScene[(UINT)eSceneType::Select]->Initialize();
		mScene[(UINT)eSceneType::STGA] = new StageA();
		mScene[(UINT)eSceneType::STGA]->Initialize();
		mScene[(UINT)eSceneType::STGB] = new StageB();
		mScene[(UINT)eSceneType::STGB]->Initialize();
		ChangeScene(eSceneType::Title);
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