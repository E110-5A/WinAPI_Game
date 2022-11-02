#include "jsPlayScene.h"
#include "jsPlayer.h"
#include "jsSceneManager.h"
#include "jsInput.h"
#include "jsCollisionManager.h"
#include "jsCamera.h"

#include "jsBGObj.h"
#include "jsMonster.h"
#include "jsGround.h"
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
		AddGameObject(bg, eColliderLayer::BackGround);

		Ground* g = new Ground();
		g->SetImage(L"PlayG", L"Play_Ground.bmp");
		g->Initialize();
		AddGameObject(g, eColliderLayer::Tile);


		GameObject* pPlayer = new Player;
		AddGameObject(pPlayer, eColliderLayer::Player);
		
		Camera::SetTarget(pPlayer);

		AddGameObject(new Monster, eColliderLayer::Monster);

		CollisionManager::SetLayer(eColliderLayer::Player, eColliderLayer::Monster, true);
		CollisionManager::SetLayer(eColliderLayer::Player_Projectile, eColliderLayer::Monster, true);

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