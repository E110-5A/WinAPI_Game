#include "jsTestScene.h"
#include "jsPlayer.h"
#include "jsMonster.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsBGObj.h"
#include "jsCollisionManager.h"
#include "jsObject.h"
#include "jsApplication.h"
#include "jsToolScene.h"
#include "jsUIManager.h"
#include "jsHUD.h"
#include "jsButton.h"

namespace js
{
	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		// 맵 로딩		
		SceneManager::LoadMap<ToolScene>(L"..\\Resources\\Tile\\testMap",eSceneType::Tool);


		// 오브젝트 추가
		GameObject* pPlayer = object::Instantiate<Player>(eColliderLayer::Player, Pos(440.f, 380.f));
		//mons[0] = object::Instantiate<Monster>(eColliderLayer::Monster);



		// ui 추가
		UIManager::Push(eUIType::TEST);
		UIManager::Push(eUIType::PLAYER_INFO);
		HUD* hud = UIManager::GetUIInstant<HUD>(eUIType::PLAYER_INFO);
		hud->SetTarget(pPlayer);
		UIManager::Push(eUIType::ITEM_SELECT);
	}

	void TestScene::Tick()
	{
		// 오브젝트 tick 을 호출한다.
		Scene::Tick();

		//js::object::Destroy(mons[0], 3.0f);
	}

	void TestScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//
		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Test Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void TestScene::Enter()
	{
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player, true);
		CollisionManager::SetLayer(eColliderLayer::Monster, eColliderLayer::Player_Projectile, true);
	}

	void TestScene::Exit()
	{
	}
}