#include "jsPlayScene.h"
#include "jsPlayer.h"
#include "jsSceneManager.h"
#include "jsInput.h"
#include "jsBGObj.h"

namespace js
{
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		BGObj* bg = new BGObj();
		bg->SetImage(L"PlayBG", L"Play_BG.bmp");
		bg->Initialize();
		AddGameObject(bg);

		BGObj* g = new BGObj();
		g->SetImage(L"PlayG", L"Play_Ground.bmp");
		g->Initialize();
		AddGameObject(g);

		AddGameObject(new Player);

	}
	void PlayScene::Tick()
	{
		Scene::Tick();
		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::ChangeScene(eSceneType::Title);
		}
	}
	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		wchar_t szFloat[40] = {};
		swprintf_s(szFloat, 40, L"Play Scene");
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void PlayScene::Enter()
	{
	}
	void PlayScene::Exit()
	{
	}
}